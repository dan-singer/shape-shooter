#pragma once
#include "Component.h"
#include <DirectXMath.h>

class MovementComponent : public Component
{
public: 

	virtual void Start() override;
	MovementComponent(Entity* entity) : Component(entity) { }

	virtual void Tick(float deltaTime) override;
	virtual void OnMouseMove(WPARAM buttonState, int x, int y) override;

	void SetSpeed(float n_speed);
	float GetSpeed();

	bool m_doShit = true;

	void SetSensitivity(float n_sense);
	float GetSensitivity();

	void GetWindow(HWND* win, unsigned int* w, unsigned int* h);

	void SetMovementControls(char forw, char back, char left, char right);
private:
	char moveForward = 'W'; //Changeable controls
	char moveBack = 'S';
	char moveLeft = 'D';
	char moveRight = 'A';
	unsigned int* width; //window width height
	unsigned int* height;
	float m_speed = 1.0f; //Speed of the player
	float m_sensitivity = 0.001f; //How quickly the camera rotates depending on mouse movemnt
	float m_pitch = 0.0f;
	float m_yaw = 0.0f;
	DirectX::XMFLOAT2 prevMousePos = DirectX::XMFLOAT2(0,0);
	HWND* hWnd;

};

