#include "DebugMovement.h"
#include "Transform.h"
#include "Entity.h"

using namespace DirectX;

void DebugMovement::Start()
{
}

void DebugMovement::Tick(float deltaTime)
{
	Transform* transform = GetOwner()->GetTransform();

	XMFLOAT3 posData = transform->GetPosition();
	XMVECTOR position = XMLoadFloat3(&posData);

	XMFLOAT3 fwdData = transform->GetForward();
	XMVECTOR globalForward = XMLoadFloat3(&fwdData);

	XMFLOAT3 rightData = transform->GetRight();
	rightData.y = 0; // We don't want the camera to move vertically when moving left or right
	XMVECTOR globalRight = XMLoadFloat3(&rightData);
	globalRight = XMVector3Normalize(globalRight);

	XMVECTOR localUp = XMVectorSet(0, 1, 0, 0);

	XMVECTOR translation = XMVectorSet(0, 0, 0, 0);
	if (GetAsyncKeyState('W') & 0x8000) {
		translation += globalForward;
	}
	if (GetAsyncKeyState('S') & 0x8000) {
		translation += -globalForward;
	}
	if (GetAsyncKeyState('A') & 0x8000) {
		translation += globalRight;
	}
	if (GetAsyncKeyState('D') & 0x8000) {
		translation += -globalRight;
	}
	if (GetAsyncKeyState(' ') & 0x8000) {
		translation += localUp;
	}
	if (GetAsyncKeyState('X') & 0x8000) {
		translation += -localUp;
	}
	translation = XMVector3Normalize(translation);
	translation *= deltaTime;
	XMVECTOR newPos = XMVectorAdd(position, translation);

	XMFLOAT3 newPosData;
	XMStoreFloat3(&newPosData, newPos);
	transform->SetPosition(newPosData);
}

void DebugMovement::OnMouseMove(WPARAM buttonState, int x, int y)
{
	// Add any custom code here...
	int dx = x - prevMousePos.x;
	int dy = y - prevMousePos.y;

	XMFLOAT4 newRotData;
	m_pitch += dy * 0.001f;
	m_yaw += dx * 0.001f;
	XMVECTOR newRot = XMQuaternionRotationRollPitchYaw(m_pitch, m_yaw, 0);
	XMStoreFloat4(&newRotData, newRot);
	GetOwner()->GetTransform()->SetRotation(newRotData);

	prevMousePos.x = x; 
	prevMousePos.y = y;
}
