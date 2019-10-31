#include "MovementComponent.h"
#include "Transform.h"
#include "Entity.h"


using namespace DirectX;

void MovementComponent::Start()
{
}

void MovementComponent::Tick(float deltaTime)
{
	Transform* transform = GetOwner()->GetTransform(); //Grabs current transform of the objec this is one

	//Grab and store our values for movement including the forward vector, right vector, and position
	XMFLOAT3 posData = transform->GetPosition();
	XMFLOAT3 fwdData = transform->GetForward();
	XMFLOAT3 rightData = transform->GetRight();

	rightData.y = 0; //We don't need this component



	//Store these in XMVectors
	XMVECTOR position = XMLoadFloat3(&posData);
	XMVECTOR g_forward = XMLoadFloat3(&fwdData);
	XMVECTOR g_right = XMLoadFloat3(&rightData);
	g_right = XMVector3Normalize(g_right); //Normalize right vector

	XMVECTOR translation = XMVectorSet(0, 0, 0, 0); //Stores the total amount the camera is moving this frame




	//Apply our given transformations
	if (GetAsyncKeyState(moveForward) & 0x8000)
	{
		translation += g_forward;
	}
	if (GetAsyncKeyState(moveBack) & 0x8000)
	{
		translation -= g_forward;
	}
	if (GetAsyncKeyState(moveRight) & 0x8000)
	{
		translation += g_right;
	}
	if (GetAsyncKeyState(moveLeft) & 0x8000)
	{
		translation -= g_right;
	}

	//Multiple by deltaTime to scale it to a reasonable amount
	translation = XMVector3Normalize(translation);
	translation *= deltaTime;
	translation *= m_speed; //Multiply that by our speed (1 < speed < 2 for decent not terrible speedy movement)

	XMVECTOR newPos = XMVectorAdd(translation, position); //Add it to the camera's position

	XMFLOAT3 newPosData;
	XMStoreFloat3(&newPosData, newPos);
	transform->SetPosition(newPosData); //Apply the change to the camera
}

void MovementComponent::OnMouseMove(WPARAM buttonState, int x, int y)
{
	int dx = x - prevMousePos.x;
	int dy = y - prevMousePos.y;

	// printf("%d %d\n", dx, dy);

	m_yaw += dx * m_sensitivity;
	m_pitch += dy * m_sensitivity;

	XMFLOAT4 rotDeltaData;
	XMVECTOR rotDelta = XMQuaternionRotationRollPitchYaw(m_pitch, m_yaw, 0.0f); //Multiply difference by sensitivity, store in a quaternion
	XMStoreFloat4(&rotDeltaData, rotDelta);
	GetOwner()->GetTransform()->SetRotation(rotDeltaData); //Apply our new rotation to the camera

	//Locking cursor to screen goes here

	prevMousePos.x = x;
	prevMousePos.y = y;
}

void MovementComponent::SetSpeed(float n_speed)
{
	m_speed = n_speed;
}

float MovementComponent::GetSpeed()
{
	return m_speed;
}

void MovementComponent::SetSensitivity(float n_sense)
{
	m_sensitivity = n_sense;
}

float MovementComponent::GetSensitivity()
{
	return m_sensitivity;
}

void MovementComponent::GetWindow(HWND* win, unsigned int* w, unsigned int* h)
{
	hWnd = win;
	width = w;
	height = h;
}

//Allows for customization of controls because why not
void MovementComponent::SetMovementControls(char forw, char back, char left, char right)
{
	moveForward = forw;
	moveBack = back;
	moveLeft = left;
	moveRight = right;
}
