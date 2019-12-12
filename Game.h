#pragma once

#include "DXCore.h"
#include "SimpleShader.h"
#include <DirectXMath.h>
#include "Mesh.h"
#include "Entity.h"
#include "CameraComponent.h"
#include "LightComponent.h"
#include <functional>

typedef std::function<void()> Action;

class Game 
	: public DXCore
{

public:
	Game(HINSTANCE hInstance);
	~Game();

	// Overridden setup and game loop methods, which
	// will be called automatically
	void Init();
	void OnResize();
	void Update(float deltaTime, float totalTime);
	void Draw(float deltaTime, float totalTime);

	// Overridden mouse input helper methods
	void OnMouseDown (WPARAM buttonState, int x, int y);
	void OnMouseUp	 (WPARAM buttonState, int x, int y);
	void OnMouseMove (WPARAM buttonState, int x, int y);
	void OnMouseWheel(float wheelDelta,   int x, int y);
private:

	float mouseYaw = 0;
	float mousePitch = 0;
	float minPitch = -.78f;
	float maxPitch = .78f;

	bool allowCameraRotation = false;

	// Initialization helper methods - feel free to customize, combine, etc.
	void LoadResources(); 
	void LoadMainMenu();
	void LoadGame();
	void LoadCredits();
	void LoadGameOver();
	float sensitivity; //Putting this here since we're decuppling mouse from the movement component
	RECT rect; //struct representing the rectangle that is our window
	// Keeps track of the old mouse position.  Useful for 
	// determining how far the mouse moved in a single frame.
	POINT prevMousePos;
};

