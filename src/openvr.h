#pragma once
#include <openvr.h>
#include "QGLView.h"
#include <QGamePad>
#include <QTime>
#include <QTimer>
#include <QOpenGLContext>
#include <QGLFormat>
#include <QOpenGLFrameBufferObject>
#include <QOffscreenSurface>
#include <QGraphicsScene>
#include "renderer.h"

#include "Matrices.h"
#include "Vectors.h"

class Debouncer
{
public:
	Debouncer(float repeatPeriod = 1.0f)
		: repeatPeriod(repeatPeriod)
		, lastState(false)
		, outputState(false)
		, repeating(false)
	{
		timer.start();
	}
	bool state() { return outputState; }
	operator bool() { return state(); }
	bool feed(bool newState);
	bool isRepeating() { return repeating; }
	bool isReleased() { return released; }
private:
	float repeatPeriod;
	QTime timer;
	bool lastState;
	bool outputState;
	bool repeating;
	bool released;
};

class Overlay
{
public:
	Overlay(QString name, QOpenGLContext* ctx);
	void setWidget(QWidget *pWidget);
	void show();
	void hide();
	void onTimeoutPumpEvents();
	void onSceneChanged();
	bool checkMouse(vr::VROverlayIntersectionParams_t const& parms, Qt::MouseButtons buttons);
	QGraphicsScene *m_pScene;
	vr::VROverlayHandle_t m_ulOverlayHandle;
private:
	QGraphicsRectItem* m_cursor;
	vr::HmdError m_eCompositorError;
	vr::HmdError m_eOverlayError, m_eLastHmdError;
	vr::Compositor_OverlaySettings m_overlaySettings;
	
	vr::VROverlayHandle_t m_ulOverlayThumbnailHandle;

	QOpenGLContext *m_pOpenGLContext;

	QOpenGLFramebufferObject *m_pFbo;
	QOffscreenSurface *m_pOffscreenSurface;

	QTimer *m_pPumpEventsTimer;

	// the widget we're drawing into the texture
	QWidget *m_pWidget;

	QPointF m_ptLastMouse;
	Qt::MouseButtons m_lastMouseButtons;
	bool m_bManualMouseHandling;
};
class VRMenu;
class OpenVR
{
public:
	OpenVR();
	void initialize();
	void renderFrame(GLView& r);
	void mainLoop(GLView& r);
	bool enabled() { return m_pHMD; }
	void UpdateHMDMatrixPose();
	QGamepad gamePad;
	QTime time;
	const double dps = 60;
	const double tps = 10;
	const double sps = 10;
	const double distps = 10;
	const double dragFactor = 20;
private:
	QGLView* q;
	VRMenu* menu;
	Overlay* menuOverlay;
	void createMenu();
	void processPad();
	void updatePad(double elapsed);
	unsigned int pick();
	Matrix4 ConvertSteamVRMatrixToMatrix4(const vr::HmdMatrix34_t &matPose);
	Matrix4 GetCurrentViewProjectionMatrix(vr::Hmd_Eye nEye);
	void RenderScene(GLView& v, vr::Hmd_Eye nEye);
	Matrix4 GetHMDMatrixProjectionEye(vr::Hmd_Eye nEye);
	Matrix4 GetHMDMatrixPoseEye(vr::Hmd_Eye nEye);
	struct FramebufferDesc
	{
		GLuint m_nDepthBufferId;
		GLuint m_nRenderTextureId;
		GLuint m_nRenderFramebufferId;
		GLuint m_nResolveTextureId;
		GLuint m_nResolveFramebufferId;
	};
	FramebufferDesc leftEyeDesc;
	FramebufferDesc rightEyeDesc;
	bool CreateFrameBuffer(int nWidth, int nHeight, FramebufferDesc &framebufferDesc);

	uint32_t m_nRenderWidth;
	uint32_t m_nRenderHeight;
	vr::IVRSystem *m_pHMD;
	vr::TrackedDevicePose_t m_rTrackedDevicePose[vr::k_unMaxTrackedDeviceCount];
	Matrix4 m_rmat4DevicePose[vr::k_unMaxTrackedDeviceCount];

	Matrix4 m_mat4HMDPose;
	Matrix4 m_mat4eyePosLeft;
	Matrix4 m_mat4eyePosRight;

	Matrix4 m_mat4ProjectionCenter;
	Matrix4 m_mat4ProjectionLeft;
	Matrix4 m_mat4ProjectionRight;

	// POV
	double target[3];
	double distance;
	double angles[3];
	double scale;
	double initialHeight;
	// button state
	Debouncer buttonL, buttonR, buttonU, buttonD, buttonX, buttonY;

	// overlays
public:
	QList<Overlay*> overlays; //fixme accessors
	QTime overlayEvents;
};
