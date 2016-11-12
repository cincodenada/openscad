#pragma once
#include <openvr.h>
#include <QGamePad>
#include <QTime>
#include "renderer.h"
#include "GLView.h"
#include "Matrices.h"

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
	const double dragFactor = 5;
private:
	void updatePad(double elapsed);
	unsigned int pick(GLView& v);
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
};
