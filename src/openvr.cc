#include "openvr.h"
#include "QGLView.h"
#include "OpenCSGRenderer.h"
#include <QApplication>
#include <QOpenglPaintDevice>
#include <QGraphicsSceneMouseEvent>
#include <QOpenGLWidget>
#include <set>
#include <QPushButton>
#include <QVBoxLayout>
/* TODO
- when cursor is in spaces, no object is selected
- VR object create
- VR object move
*/


class VRMenu : public QWidget
{
public:
	VRMenu();
	QPushButton* bOk, * bCancel;
	QVBoxLayout* layout;
};

VRMenu::VRMenu()
{
	layout = new QVBoxLayout();
	setLayout(layout);
	bOk = new QPushButton("OK");
	bCancel = new QPushButton("Cancel");
	layout->addWidget(bOk);
	layout->addWidget(bCancel);
	setStyleSheet("background-color:black;");
	QPalette pal = palette();
	pal.setColor(QPalette::Window, Qt::black);
	this->setPalette(pal);
	setAutoFillBackground(true);
	bOk->show();
	bCancel->show();
	show();
}

OpenVR::OpenVR()
	: target{0,0,0}
	, angles{0,0,0}
{
	m_pHMD = NULL;
	distance = 0;
	overlayEvents.start();
}

void OpenVR::initialize()
{
	vr::EVRInitError eError = vr::VRInitError_None;
	m_pHMD = vr::VR_Init(&eError, vr::VRApplication_Scene);

	if (eError != vr::VRInitError_None)
	{
		m_pHMD = NULL;
		return;
	}
	vr::VRCompositor();
	m_pHMD->GetRecommendedRenderTargetSize(&m_nRenderWidth, &m_nRenderHeight);
	CreateFrameBuffer(m_nRenderWidth, m_nRenderHeight, leftEyeDesc);
	CreateFrameBuffer(m_nRenderWidth, m_nRenderHeight, rightEyeDesc);
	m_mat4ProjectionLeft = GetHMDMatrixProjectionEye(vr::Eye_Left);
	m_mat4ProjectionRight = GetHMDMatrixProjectionEye(vr::Eye_Right);
	m_mat4eyePosLeft = GetHMDMatrixPoseEye(vr::Eye_Left);
	m_mat4eyePosRight = GetHMDMatrixPoseEye(vr::Eye_Right);
	time.start();
}

bool OpenVR::CreateFrameBuffer(int nWidth, int nHeight, FramebufferDesc &framebufferDesc)
{
	glGenFramebuffers(1, &framebufferDesc.m_nRenderFramebufferId);
	glBindFramebuffer(GL_FRAMEBUFFER, framebufferDesc.m_nRenderFramebufferId);

	glGenRenderbuffers(1, &framebufferDesc.m_nDepthBufferId);
	glBindRenderbuffer(GL_RENDERBUFFER, framebufferDesc.m_nDepthBufferId);
	glRenderbufferStorageMultisample(GL_RENDERBUFFER, 4, GL_DEPTH_COMPONENT, nWidth, nHeight);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, framebufferDesc.m_nDepthBufferId);

	glGenTextures(1, &framebufferDesc.m_nRenderTextureId);
	glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, framebufferDesc.m_nRenderTextureId);
	glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, 4, GL_RGBA8, nWidth, nHeight, true);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, framebufferDesc.m_nRenderTextureId, 0);

	glGenFramebuffers(1, &framebufferDesc.m_nResolveFramebufferId);
	glBindFramebuffer(GL_FRAMEBUFFER, framebufferDesc.m_nResolveFramebufferId);

	glGenTextures(1, &framebufferDesc.m_nResolveTextureId);
	glBindTexture(GL_TEXTURE_2D, framebufferDesc.m_nResolveTextureId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, nWidth, nHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, framebufferDesc.m_nResolveTextureId, 0);

	// check FBO status
	GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (status != GL_FRAMEBUFFER_COMPLETE)
	{
		return false;
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	return true;
}

Matrix4 OpenVR::GetCurrentViewProjectionMatrix(vr::Hmd_Eye nEye)
{
	Matrix4 matMVP;
	if (nEye == vr::Eye_Left)
	{
		matMVP = m_mat4ProjectionLeft * m_mat4eyePosLeft * m_mat4HMDPose;
	}
	else if (nEye == vr::Eye_Right)
	{
		matMVP = m_mat4ProjectionRight * m_mat4eyePosRight *  m_mat4HMDPose;
	}

	return matMVP;
}

void OpenVR::RenderScene(GLView& v, vr::Hmd_Eye nEye)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(GetCurrentViewProjectionMatrix(nEye).get());
	glMatrixMode(GL_MODELVIEW);
	glTranslated(distance, 0, 0);
	glRotated(angles[0], 1, 0, 0);
	glRotated(angles[1], 0, 1, 0);
	glRotated(angles[2], 0, 0, 1);
	glTranslated(target[0], target[1], target[2]);
	v.paintGL(false, false);
}

unsigned int OpenVR::pick(GLView& v)
{
	auto& q = dynamic_cast<QGLView&>(v);
	q.makeCurrent();
	OpenCSGRenderer* o = dynamic_cast<OpenCSGRenderer*>(q.getRenderer());
	if (!o)
		return 0;
	o->setPicking(true);
	int width = v.cam.pixel_width;
	int height = v.cam.pixel_height;
	glViewport(0, 0, width, height);
	RenderScene(v, vr::Eye_Left);
	glGetError();
	unsigned int hit = 0;
	glReadPixels(width / 2, height / 2,
		1, 1, GL_RGBA, GL_UNSIGNED_BYTE, &hit);
	auto err = glGetError();
	if (err != GL_NO_ERROR)
	{
		std::cerr << "READPIXELS: " << err << std::endl;
		std::cerr << gluErrorString(err) << std::endl;
	}
	hit = ((hit & 0xFC) >> 2) + ((hit & 0xFC00) >> 4) + ((hit & 0xFC0000) >> 6);
    std::cerr << hit << std::endl;
	o->setPicking(false);
	return hit;
}

void OpenVR::renderFrame(GLView& v)
{
	auto& q = dynamic_cast<QGLView&>(v);
	q.makeCurrent();
	glClearColor(0.15f, 0.15f, 0.18f, 1.0f); // nice background color, but not black
	glEnable(GL_MULTISAMPLE);

	// Left Eye
	glBindFramebuffer(GL_FRAMEBUFFER, leftEyeDesc.m_nRenderFramebufferId);
	glViewport(0, 0, m_nRenderWidth, m_nRenderHeight);
	RenderScene(v, vr::Eye_Left);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glDisable(GL_MULTISAMPLE);

	glBindFramebuffer(GL_READ_FRAMEBUFFER, leftEyeDesc.m_nRenderFramebufferId);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, leftEyeDesc.m_nResolveFramebufferId);

	glBlitFramebuffer(0, 0, m_nRenderWidth, m_nRenderHeight, 0, 0, m_nRenderWidth, m_nRenderHeight,
		GL_COLOR_BUFFER_BIT,
		GL_LINEAR);
	glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

	glEnable(GL_MULTISAMPLE);

	// Right Eye
	glBindFramebuffer(GL_FRAMEBUFFER, rightEyeDesc.m_nRenderFramebufferId);
	glViewport(0, 0, m_nRenderWidth, m_nRenderHeight);
	RenderScene(v, vr::Eye_Right);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glDisable(GL_MULTISAMPLE);

	glBindFramebuffer(GL_READ_FRAMEBUFFER, rightEyeDesc.m_nRenderFramebufferId);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, rightEyeDesc.m_nResolveFramebufferId);

	glBlitFramebuffer(0, 0, m_nRenderWidth, m_nRenderHeight, 0, 0, m_nRenderWidth, m_nRenderHeight,
		GL_COLOR_BUFFER_BIT,
		GL_LINEAR);

	glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

	vr::Texture_t leftEyeTexture = { (void*)leftEyeDesc.m_nResolveTextureId, vr::API_OpenGL, vr::ColorSpace_Gamma };
	vr::VRCompositor()->Submit(vr::Eye_Left, &leftEyeTexture);
	vr::Texture_t rightEyeTexture = { (void*)rightEyeDesc.m_nResolveTextureId, vr::API_OpenGL, vr::ColorSpace_Gamma };
	vr::VRCompositor()->Submit(vr::Eye_Right, &rightEyeTexture);
}


void OpenVR::UpdateHMDMatrixPose()
{
	if (!m_pHMD)
		return;

	vr::VRCompositor()->WaitGetPoses(m_rTrackedDevicePose, vr::k_unMaxTrackedDeviceCount, NULL, 0);

	for (int nDevice = 0; nDevice < vr::k_unMaxTrackedDeviceCount; ++nDevice)
	{
		if (m_rTrackedDevicePose[nDevice].bPoseIsValid)
		{
			m_rmat4DevicePose[nDevice] = ConvertSteamVRMatrixToMatrix4(m_rTrackedDevicePose[nDevice].mDeviceToAbsoluteTracking);
			/*
			if (m_rDevClassChar[nDevice] == 0)
			{
				switch (m_pHMD->GetTrackedDeviceClass(nDevice))
				{
				case vr::TrackedDeviceClass_Controller:        m_rDevClassChar[nDevice] = 'C'; break;
				case vr::TrackedDeviceClass_HMD:               m_rDevClassChar[nDevice] = 'H'; break;
				case vr::TrackedDeviceClass_Invalid:           m_rDevClassChar[nDevice] = 'I'; break;
				case vr::TrackedDeviceClass_Other:             m_rDevClassChar[nDevice] = 'O'; break;
				case vr::TrackedDeviceClass_TrackingReference: m_rDevClassChar[nDevice] = 'T'; break;
				default:                                       m_rDevClassChar[nDevice] = '?'; break;
				}
			}
			m_strPoseClasses += m_rDevClassChar[nDevice];
			*/
		}
	}

	if (m_rTrackedDevicePose[vr::k_unTrackedDeviceIndex_Hmd].bPoseIsValid)
	{
		m_mat4HMDPose = m_rmat4DevicePose[vr::k_unTrackedDeviceIndex_Hmd].invert();
	}
}

Matrix4 OpenVR::ConvertSteamVRMatrixToMatrix4(const vr::HmdMatrix34_t &matPose)
{
	Matrix4 matrixObj(
		matPose.m[0][0], matPose.m[1][0], matPose.m[2][0], 0.0,
		matPose.m[0][1], matPose.m[1][1], matPose.m[2][1], 0.0,
		matPose.m[0][2], matPose.m[1][2], matPose.m[2][2], 0.0,
		matPose.m[0][3], matPose.m[1][3], matPose.m[2][3], 1.0f
	);
	return matrixObj;
}

Matrix4 OpenVR::GetHMDMatrixProjectionEye(vr::Hmd_Eye nEye)
{
	if (!m_pHMD)
		return Matrix4();

	vr::HmdMatrix44_t mat = m_pHMD->GetProjectionMatrix(nEye, 0.3, 300.0, vr::API_OpenGL);

	return Matrix4(
		mat.m[0][0], mat.m[1][0], mat.m[2][0], mat.m[3][0],
		mat.m[0][1], mat.m[1][1], mat.m[2][1], mat.m[3][1],
		mat.m[0][2], mat.m[1][2], mat.m[2][2], mat.m[3][2],
		mat.m[0][3], mat.m[1][3], mat.m[2][3], mat.m[3][3]
	);
}


//-----------------------------------------------------------------------------
// Purpose:
//-----------------------------------------------------------------------------
Matrix4 OpenVR::GetHMDMatrixPoseEye(vr::Hmd_Eye nEye)
{
	if (!m_pHMD)
		return Matrix4();

	vr::HmdMatrix34_t matEyeRight = m_pHMD->GetEyeToHeadTransform(nEye);
	Matrix4 matrixObj(
		matEyeRight.m[0][0], matEyeRight.m[1][0], matEyeRight.m[2][0], 0.0,
		matEyeRight.m[0][1], matEyeRight.m[1][1], matEyeRight.m[2][1], 0.0,
		matEyeRight.m[0][2], matEyeRight.m[1][2], matEyeRight.m[2][2], 0.0,
		matEyeRight.m[0][3], matEyeRight.m[1][3], matEyeRight.m[2][3], 1.0f
	);

	return matrixObj.invert();
}

void OpenVR::updatePad(double elapsed)
{
	double dx = gamePad.axisLeftX() * elapsed * dps;
	double dy = gamePad.axisLeftY() * elapsed * dps;
	angles[0] += dx;
	angles[1] += dy;
	angles[2] += gamePad.buttonL1() * elapsed * dps;
	angles[2] -= gamePad.buttonL2() * elapsed * dps;
	target[0] += gamePad.axisRightX() * elapsed * tps;
	target[1] += gamePad.axisRightY() * elapsed * tps;
	target[2] += gamePad.buttonR1() * elapsed * tps;
	target[2] -= gamePad.buttonR2() * elapsed * tps;
	distance += gamePad.buttonUp() * elapsed * distps;
	distance -= gamePad.buttonDown() * elapsed * distps;
}

void OpenVR::mainLoop(GLView& v)
{
	auto& q = dynamic_cast<QGLView&>(v);
	auto* vrm = new VRMenu();
	auto* over = new Overlay("menu", q.context());// nullptr);
	vrm->repaint();
	over->setWidget(vrm);
	QBrush brush;
	brush.setColor(Qt::red);
	over->m_pScene->addRect(5, 5, 500, 500, QPen(), brush);
	over->m_pScene->setBackgroundBrush(Qt::blue);
	
	vr::HmdMatrix34_t mat;
	memset(mat.m, 0, sizeof(mat.m));
	/*
	mat.m[0][0] = 1;
	mat.m[1][1] = 1;
	mat.m[2][2] = 1;
	//mat.m[2][3] = 2;
	vr::VROverlay()->SetOverlayTransformAbsolute(
		over->m_ulOverlayHandle,
		vr::TrackingUniverseOrigin::TrackingUniverseSeated,
		&mat);
	*/
	vr::TrackingUniverseOrigin orig;
	vr::VROverlay()->GetOverlayTransformAbsolute(over->m_ulOverlayHandle, &orig, &mat);
	for (int i = 0; i < 3; ++i)
		std::cerr << mat.m[i][0] << ' ' << mat.m[i][1] << ' ' << mat.m[i][2] << "  " << mat.m[i][3] << std::endl;
	overlays.push_back(over);
	over->onSceneChanged();
	while (true)
	{
		if (overlayEvents.elapsed() > 20)
		{
			//for (auto& o : overlays)
			//	o->onTimeoutPumpEvents();
			overlayEvents.restart();
			//over->onSceneChanged();
		}
		QApplication::processEvents();
		UpdateHMDMatrixPose();
		double elapsed = time.restart() / 1000.0;
		buttonL.feed(gamePad.buttonLeft());
		buttonR.feed(gamePad.buttonRight());
		buttonU.feed(gamePad.buttonUp());
		buttonD.feed(gamePad.buttonDown());
		buttonX.feed(gamePad.buttonX());
		buttonY.feed(gamePad.buttonY());
		if (buttonY.isRepeating())
			over->hide();
		if (buttonX.isRepeating())
		{
			over->show();
			over->onSceneChanged();
		}
		if (buttonX)
		{
			unsigned int id = pick(v);
			
			if (id > 0 && id < 65000)
			{
				int prev = q.last_pick_id;
				q.last_pick_id = id;
				emit q.pickedObject(id, prev, Qt::ControlModifier);
			}
			else
				q.last_pick_id = 0;
		}
		else if (gamePad.buttonY() || gamePad.buttonA() || gamePad.buttonB())
		{
			bool tie = gamePad.buttonR1();
			bool slow = gamePad.buttonR2();
			double factor = dragFactor * (slow? 0.2 : 1.0); // gamePad.buttonY() ? tps : gamePad.buttonA() ? dps : sps;
			auto mod = gamePad.buttonA() ? Qt::AltModifier : gamePad.buttonB() ? Qt::ShiftModifier : 0;
			double dx = gamePad.axisLeftX() * elapsed * factor;
			double dy = gamePad.axisLeftY() * elapsed * factor;
			double dz = gamePad.buttonL1() * elapsed * factor;
			dz -= gamePad.buttonL2() * elapsed * factor;
			if (tie)
				dy = dz = dx+dy;
			emit q.dragObject(q.last_pick_id, 0, dx, dx, Qt::MouseButton::LeftButton, mod);
			emit q.dragObject(q.last_pick_id, 1, dy, dy, Qt::MouseButton::LeftButton, mod);
			emit q.dragObject(q.last_pick_id, 2, dz, dz, Qt::MouseButton::LeftButton, mod);
		}
		else if (q.last_pick_id &&
			(buttonL || buttonR || buttonU ||  buttonD))
		{
			int key = buttonL ? Qt::Key_Left : buttonR ? Qt::Key_Right
				: buttonU ? Qt::Key_Up : Qt::Key_Down;
			Qt::KeyboardModifiers mod = 0;
			emit q.keyPress(key, mod);
		}
		else
			updatePad(elapsed);
		renderFrame(v);
	}
}

bool Debouncer::feed(bool newState)
{
	if (!newState)
	{
		lastState = outputState = repeating = false;
		timer.restart();
	}
	else if (!lastState)
	{
		timer.restart();
		lastState = outputState = true;
	}
	else if (outputState)
	{
		outputState = false;
		timer.restart();
	}
	else if (timer.elapsed() / 1000.0f > repeatPeriod)
	{
		repeating = true;
		outputState = true;
	}
	return outputState;
}


Overlay::Overlay(QString name, QOpenGLContext* ctx)
: m_eLastHmdError(vr::VRInitError_None)
, m_eCompositorError(vr::VRInitError_None)
, m_eOverlayError(vr::VRInitError_None)
, m_pOpenGLContext(ctx)
, m_pScene(NULL)
, m_pOffscreenSurface(NULL)
, m_pFbo(NULL)
, m_pWidget(NULL)
, m_pPumpEventsTimer(NULL)
, m_lastMouseButtons(0)
, m_ulOverlayHandle(vr::k_ulOverlayHandleInvalid)
, m_bManualMouseHandling(false)
{
	bool bSuccess = true;
	if (!ctx)
	{
		QSurfaceFormat format;
		format.setMajorVersion(4);
		format.setMinorVersion(1);
		format.setProfile(QSurfaceFormat::CompatibilityProfile);

		m_pOpenGLContext = new QOpenGLContext();
		m_pOpenGLContext->setFormat(format);
		bSuccess = m_pOpenGLContext->create();
		if (!bSuccess)
			throw std::runtime_error("Unable to create context");
	}
	// create an offscreen surface to attach the context and FBO to
	m_pOffscreenSurface = new QOffscreenSurface();
	m_pOffscreenSurface->create();
	m_pOpenGLContext->makeCurrent(m_pOffscreenSurface);

	m_pScene = new QGraphicsScene();
	QObject::connect(m_pScene, &QGraphicsScene::changed, [this] { this->onSceneChanged(); });
	//connect(m_pScene, SIGNAL(changed(const QList<QRectF>&)), this, SLOT(OnSceneChanged(const QList<QRectF>&)));

	bSuccess = bSuccess && vr::VRCompositor() != NULL;

	if (vr::VROverlay())
	{
		std::string sKey = std::string("openscad.") + name.toStdString();
		vr::VROverlayError overlayError = vr::VROverlay()->CreateOverlay(sKey.c_str(), sKey.c_str(), &m_ulOverlayHandle);
		bSuccess = bSuccess && overlayError == vr::VROverlayError_None;
	}

	if (bSuccess)
	{
		vr::VROverlay()->SetOverlayColor(m_ulOverlayHandle, 0.2, 0.4, 0.6);
		vr::VROverlay()->SetOverlayWidthInMeters(m_ulOverlayHandle, 1.5f);
		vr::VROverlay()->SetOverlayInputMethod(m_ulOverlayHandle, vr::VROverlayInputMethod_Mouse);
		vr::VROverlay()->SetOverlayAlpha(m_ulOverlayHandle, 0.5);
		/*
		m_pPumpEventsTimer = new QTimer(this);
		m_pPumpEventsTimer->connect(m_pPumpEventsTimer, &QTimer::timeout),
			[this] {this->onTimeoutPumpEvents(); });
		m_pPumpEventsTimer->setInterval(20);
		m_pPumpEventsTimer->start();
		*/
	}
	if (!bSuccess)
		throw std::runtime_error("Overlay initialization failure");
}

void Overlay::setWidget(QWidget *pWidget)
{
	std::cerr << "setwidget " << (!!m_pScene) << " " << pWidget->width() << " " << pWidget->height() << std::endl;
	if (m_pScene)
	{
		// all of the mouse handling stuff requires that the widget be at 0,0
		pWidget->move(0, 0);
		m_pScene->addWidget(pWidget);
	}
	m_pWidget = pWidget;

	m_pFbo = new QOpenGLFramebufferObject(pWidget->width(), pWidget->height(), GL_TEXTURE_2D);

	if (vr::VROverlay())
	{
		vr::HmdVector2_t vecWindowSize =
		{
			(float)pWidget->width(),
			(float)pWidget->height()
		};
		vr::VROverlay()->SetOverlayMouseScale(m_ulOverlayHandle, &vecWindowSize);
	}
}
void Overlay::show()
{
	vr::VROverlay()->ShowOverlay(m_ulOverlayHandle);
}
void Overlay::hide()
{
	vr::VROverlay()->HideOverlay(m_ulOverlayHandle);
}

void Overlay::onTimeoutPumpEvents()
{
	if (!vr::VRSystem())
		return;
	std::cerr << "pumping events" << std::endl;

	if (m_bManualMouseHandling)
	{
		// tell OpenVR to make some events for us
		for (vr::TrackedDeviceIndex_t unDeviceId = 1; unDeviceId < vr::k_unControllerStateAxisCount; unDeviceId++)
		{
			if (vr::VROverlay()->HandleControllerOverlayInteractionAsMouse(m_ulOverlayHandle, unDeviceId))
			{
				break;
			}
		}
	}

	vr::VREvent_t vrEvent;
	while (vr::VROverlay()->PollNextOverlayEvent(m_ulOverlayHandle, &vrEvent, sizeof(vrEvent)))
	{
		switch (vrEvent.eventType)
		{
		case vr::VREvent_MouseMove:
		{
			QPointF ptNewMouse(vrEvent.data.mouse.x, vrEvent.data.mouse.y);
			QPoint ptGlobal = ptNewMouse.toPoint();
			QGraphicsSceneMouseEvent mouseEvent(QEvent::GraphicsSceneMouseMove);
			mouseEvent.setWidget(NULL);
			mouseEvent.setPos(ptNewMouse);
			mouseEvent.setScenePos(ptGlobal);
			mouseEvent.setScreenPos(ptGlobal);
			mouseEvent.setLastPos(m_ptLastMouse);
			mouseEvent.setLastScenePos(m_pWidget->mapToGlobal(m_ptLastMouse.toPoint()));
			mouseEvent.setLastScreenPos(m_pWidget->mapToGlobal(m_ptLastMouse.toPoint()));
			mouseEvent.setButtons(m_lastMouseButtons);
			mouseEvent.setButton(Qt::NoButton);
			mouseEvent.setModifiers(0);
			mouseEvent.setAccepted(false);

			m_ptLastMouse = ptNewMouse;
			QApplication::sendEvent(m_pScene, &mouseEvent);

			onSceneChanged();
		}
		break;

		case vr::VREvent_MouseButtonDown:
		{
			Qt::MouseButton button = vrEvent.data.mouse.button == vr::VRMouseButton_Right ? Qt::RightButton : Qt::LeftButton;

			m_lastMouseButtons |= button;

			QPoint ptGlobal = m_ptLastMouse.toPoint();
			QGraphicsSceneMouseEvent mouseEvent(QEvent::GraphicsSceneMousePress);
			mouseEvent.setWidget(NULL);
			mouseEvent.setPos(m_ptLastMouse);
			mouseEvent.setButtonDownPos(button, m_ptLastMouse);
			mouseEvent.setButtonDownScenePos(button, ptGlobal);
			mouseEvent.setButtonDownScreenPos(button, ptGlobal);
			mouseEvent.setScenePos(ptGlobal);
			mouseEvent.setScreenPos(ptGlobal);
			mouseEvent.setLastPos(m_ptLastMouse);
			mouseEvent.setLastScenePos(ptGlobal);
			mouseEvent.setLastScreenPos(ptGlobal);
			mouseEvent.setButtons(m_lastMouseButtons);
			mouseEvent.setButton(button);
			mouseEvent.setModifiers(0);
			mouseEvent.setAccepted(false);

			QApplication::sendEvent(m_pScene, &mouseEvent);
		}
		break;

		case vr::VREvent_MouseButtonUp:
		{
			Qt::MouseButton button = vrEvent.data.mouse.button == vr::VRMouseButton_Right ? Qt::RightButton : Qt::LeftButton;
			m_lastMouseButtons &= ~button;

			QPoint ptGlobal = m_ptLastMouse.toPoint();
			QGraphicsSceneMouseEvent mouseEvent(QEvent::GraphicsSceneMouseRelease);
			mouseEvent.setWidget(NULL);
			mouseEvent.setPos(m_ptLastMouse);
			mouseEvent.setScenePos(ptGlobal);
			mouseEvent.setScreenPos(ptGlobal);
			mouseEvent.setLastPos(m_ptLastMouse);
			mouseEvent.setLastScenePos(ptGlobal);
			mouseEvent.setLastScreenPos(ptGlobal);
			mouseEvent.setButtons(m_lastMouseButtons);
			mouseEvent.setButton(button);
			mouseEvent.setModifiers(0);
			mouseEvent.setAccepted(false);

			QApplication::sendEvent(m_pScene, &mouseEvent);
		}
		break;

		case vr::VREvent_OverlayShown:
		{
			m_pWidget->repaint();
		}
		break;

		case vr::VREvent_Quit:
			QApplication::exit();
			break;
		}
	}
}

void Overlay::onSceneChanged()
{
	if (!vr::VROverlay() ||
		!vr::VROverlay()->IsOverlayVisible(m_ulOverlayHandle))
		return;
	std::cerr << "VISIBLE " << std::endl;
	m_pOpenGLContext->makeCurrent(m_pOffscreenSurface);
	m_pFbo->bind();
	{
		QOpenGLPaintDevice device(m_pFbo->size());
		QPainter painter(&device);

		m_pScene->render(&painter);
	}
	m_pFbo->release();
	//m_pOpenGLContext->doneCurrent();
	GLuint unTexture = m_pFbo->texture();
	if (unTexture != 0)
	{
		vr::Texture_t texture = { (void*)unTexture, vr::API_OpenGL, vr::ColorSpace_Auto };
		vr::VROverlay()->SetOverlayTexture(m_ulOverlayHandle, &texture);
	}

}