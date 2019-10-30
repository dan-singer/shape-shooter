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

	//Store these in XMVectors
	XMVECTOR position = XMLoadFloat3(&posData);
	XMVECTOR g_forward = XMLoadFloat3(&fwdData);
	XMVECTOR g_right = XMLoadFloat3(&rightData);
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

	XMVECTOR newPos = translation + position; //Add it to the camera's position

	XMFLOAT3 newPosData;
	XMStoreFloat3(&newPosData, newPos);
	transform->SetPosition(newPosData); //Apply the change to the camera
}

void MovementComponent::OnMouseMove(WPARAM buttonState, int x, int y)
{


	RECT windowLoc;
	GetWindowRect(*hWnd, &windowLoc);

	int dx = windowLoc.left + x - prevMousePos.x;
	int dy = windowLoc.top + y - prevMousePos.y;

	printf("%d %d\n", dx, dy);

	XMFLOAT4 rotDeltaData;
	XMVECTOR rotDelta = XMQuaternionRotationRollPitchYaw(dy * m_sensitivity, dx * m_sensitivity, 0.0f); //Multiply difference by sensitivity, store in a quaternion
	XMStoreFloat4(&rotDeltaData, rotDelta);
	GetOwner()->GetTransform()->Rotate(rotDeltaData); //Apply our new rotation to the camera

	//Locking cursor to screen goes here

	prevMousePos.x = (windowLoc.left + (*width / 2));
	prevMousePos.y = (windowLoc.top + (*height / 2));
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
