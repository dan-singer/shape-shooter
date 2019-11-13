#include "Game.h"
#include "Vertex.h"
#include <WICTextureLoader.h>
#include "DDSTextureLoader.h"
#include <time.h>
#include "Transform.h"
#include "MaterialComponent.h"
#include "DebugMovement.h"
#include "MovementComponent.h"
#include "World.h"
#include "Rotator.h"
#include "RigidBodyComponent.h"
#include "CollisionTester.h"
#include "ShapeSpawnerManager.h"
#include "Launcher.h"
#include "AmmoVisualizer.h"

// For the DirectX Math library
using namespace DirectX;

// --------------------------------------------------------
// Constructor
//
// DXCore (base class) constructor will set up underlying fields.
// DirectX itself, and our window, are not ready yet!
//
// hInstance - the application's OS-level handle (unique ID)
// --------------------------------------------------------
Game::Game(HINSTANCE hInstance)
	: DXCore(
		hInstance,		   // The application's handle
		"DirectX Game",	   // Text for the window's title bar
		1280,			   // Width of the window's client area
		720,			   // Height of the window's client area
		true)			   // Show extra stats (fps) in title bar?
{

	prevMousePos = { 0,0 };

#if defined(DEBUG) || defined(_DEBUG)
	// Do we want a console window?  Probably only in debug mode
	CreateConsoleWindow(500, 120, 32, 120);
	printf("Console window created successfully.  Feel free to printf() here.\n");
#endif
	
}

Game::~Game()
{
	
}

// --------------------------------------------------------
// Called once per program, after DirectX and the window
// are initialized but before the game loop.
// --------------------------------------------------------
void Game::Init()
{
	sensitivity = 1.2;
	GetClientRect(hWnd, &rect);

	SetCursorPos(rect.left + ( (rect.right - rect.left)/ 2), rect.top + ((rect.bottom - rect.top) / 2));

	ShowCursor(false);

	LoadResources();
	CreateEntities();	
	World::GetInstance()->Start();
	// Tell the input assembler stage of the pipeline what kind of
	// geometric primitives (points, lines or triangles) we want to draw.  
	// Essentially: "What kind of shape should the GPU draw with our data?"
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	//ShowCursor(false);
}

// --------------------------------------------------------
// Loads shaders from compiled shader object (.cso) files using
// my SimpleShader wrapper for DirectX shader manipulation.
// - SimpleShader provides helpful methods for sending
//   data to individual variables on the GPU
// --------------------------------------------------------
void Game::LoadResources()
{
	World* world = World::GetInstance();

	// Meshes
	world->CreateMesh("cube", "Assets/Models/cube.obj", device);
	world->CreateMesh("cone", "Assets/Models/cone.obj", device);
	world->CreateMesh("cylinder", "Assets/Models/cylinder.obj", device);
	world->CreateMesh("helix", "Assets/Models/helix.obj", device);
	world->CreateMesh("sphere", "Assets/Models/sphere.obj", device);
	world->CreateMesh("torus", "Assets/Models/torus.obj", device);

	// Shaders
	SimpleVertexShader* vs = world->CreateVertexShader("vs", device, context, L"VertexShader.cso");
	SimplePixelShader* uiPs = world->CreatePixelShader("ui", device, context, L"UIPixelShader.cso");
	SimplePixelShader* ps  = world->CreatePixelShader("ps", device, context, L"PixelShader.cso");
	//sky shaders
	SimpleVertexShader* vsSky = world->CreateVertexShader("vsSky", device, context, L"VSSkyBox.cso");
	SimplePixelShader* psSky = world->CreatePixelShader("psSky", device, context, L"PSSkyBox.cso");

	// Textures
	world->CreateTexture("leather", device, context, L"Assets/Textures/Leather.jpg");
	world->CreateTexture("metal", device, context, L"Assets/Textures/BareMetal.png");
	world->CreateTexture("velvet_normal", device, context, L"Assets/Textures/Velvet_N.jpg");

	//skyTexture
	world->CreateCubeTexture("sky", device, context, L"Assets/Textures/SunnyCubeMap.dds");

	// Create the sampler state
	D3D11_SAMPLER_DESC samplerDesc = {};
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;
	world->CreateSamplerState("main", &samplerDesc, device);

	world->CreateMaterial("leather", vs, ps, world->GetTexture("leather"), world->GetTexture("velvet_normal"), world->GetSamplerState("main"));
	world->CreateMaterial("metal", vs, ps, world->GetTexture("metal"), world->GetTexture("velvet_normal"), world->GetSamplerState("main"));
	world->CreateMaterial("metalUI", vs, uiPs, world->GetTexture("metal"), world->GetTexture("velvet_normal"), world->GetSamplerState("main"));

	//Skybox stuff
	D3D11_RASTERIZER_DESC rd = {};
	rd.FillMode = D3D11_FILL_SOLID;
	rd.CullMode = D3D11_CULL_FRONT;
	world->CreateRasterizerState("skyRastState", &rd, device);

	D3D11_DEPTH_STENCIL_DESC ds = {};
	ds.DepthEnable = true;
	ds.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	ds.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
	world->CreateDepthStencilState("skyDepthState", &ds, device);
}


void Game::CreateEntities()
{
	World* world = World::GetInstance();

	Entity* ShapeSpawnManager = world->Instantiate("ShapeSpawnManager");
	ShapeSpawnerManagerComponent* ss = ShapeSpawnManager->AddComponent<ShapeSpawnerManagerComponent>();

	Entity* camera = world->Instantiate("Cam");
	CameraComponent* cc = camera->AddComponent<CameraComponent>();
	cc->UpdateProjectionMatrix((float)width / height);
	camera->GetTransform()->SetPosition(XMFLOAT3(0, 0, -5));
	MovementComponent* mc = camera->AddComponent<MovementComponent>();
	mc->SetSpeed(1.5f); // ** SET SPEED FOR MOVEMENT HERE **
	mc->SetSensitivity(0.002f); // ** SET SENSITIVITY OF CAMERA HERE **
	mc->GetWindow(&hWnd, &width, &height); //Get window as a pointer

	Launcher* launcher = camera->AddComponent<Launcher>();
	launcher->SetAmmoMaterial(world->GetMaterial("metal"));
	launcher->AddAmmoMesh(world->GetMesh("cube"));
	launcher->AddAmmoMesh(world->GetMesh("cone"));
	launcher->AddAmmoMesh(world->GetMesh("cylinder"));
	launcher->AddAmmoMesh(world->GetMesh("sphere"));
	launcher->AddAmmoMesh(world->GetMesh("helix"));
	launcher->AddAmmoMesh(world->GetMesh("torus"));


	world->m_mainCamera = cc;


	// Ammo Visualizer
	Entity* ammoVis = world->Instantiate("ammo visualizer");
	ammoVis->AddComponent<MeshComponent>();
	ammoVis->AddComponent<MaterialComponent>()->m_material = world->GetMaterial("metalUI");
	ammoVis->AddComponent<AmmoVisualizer>()->SetParent(camera);
	ammoVis->GetTransform()->SetScale(XMFLOAT3(.5f, .5f, .5f));
	ammoVis->GetTransform()->SetPosition(XMFLOAT3(-1.5f, -0.8f, 3));
	ammoVis->AddTag("ui");

	// Light Entities
	Entity* dirLight = world->Instantiate("DirLight1");
	LightComponent* dirLightComp = dirLight->AddComponent<LightComponent>();
	dirLightComp->m_data.type = LightComponent::Directional;
	dirLightComp->m_data.color = XMFLOAT3(1.0f, 1.0f, 1.0f);
	dirLightComp->m_data.intensity = 1.0f;
	
	/*
	Entity* pointLight = world->Instantiate("PointLight1");
	LightComponent* pointLightComp = pointLight->AddComponent<LightComponent>();
	pointLightComp->m_data.type = LightComponent::Point;
	pointLightComp->m_data.color = XMFLOAT3(1.0f, 0, 0);
	pointLightComp->m_data.intensity = 1.0f;
	pointLight->GetTransform()->SetPosition(XMFLOAT3(-1, 1, 0));

	Entity* spotLight = world->Instantiate("SpotLight1");
	LightComponent* spotLightComp = spotLight->AddComponent<LightComponent>();
	spotLightComp->m_data.type = LightComponent::Spot;
	spotLightComp->m_data.color = XMFLOAT3(0, 1.0f, 0);
	spotLightComp->m_data.intensity = 1.0f;
	spotLightComp->m_data.spotFalloff = 1.0f;
	spotLight->GetTransform()->SetPosition(XMFLOAT3(1, 1, 0));
	XMFLOAT4 spotLightRot;
	XMStoreFloat4(&spotLightRot, XMQuaternionRotationRollPitchYaw(0, 90.0f, 0));
	spotLight->GetTransform()->SetRotation(spotLightRot);
	*/
}

// --------------------------------------------------------
// Handle resizing DirectX "stuff" to match the new window size.
// For instance, updating our projection matrix's aspect ratio.
// --------------------------------------------------------
void Game::OnResize()
{
	// Handle base-level DX resize stuff
	DXCore::OnResize();
	World::GetInstance()->OnResize(width, height);
}

// --------------------------------------------------------
// Update your game here - user input, move objects, AI, etc.
// --------------------------------------------------------
void Game::Update(float deltaTime, float totalTime)
{
	//MOUSE MOVEMENT
	 // Get current position
	POINT cursorPos = {};
	GetCursorPos(&cursorPos);

	// Calculate mouse movement for this frame
	// Use this for anything that cares about
	// mouse movement, like the camera!
	int mouseMoveX = cursorPos.x - prevMousePos.x;
	int mouseMoveY = cursorPos.y - prevMousePos.y;

	float yaw = mouseMoveX * sensitivity * deltaTime;
	float pitch = mouseMoveY * sensitivity * deltaTime;

	mouseYaw += yaw;
	mousePitch += pitch;

	XMFLOAT4 rotDeltaData;
	XMVECTOR rotDelta = XMQuaternionRotationRollPitchYaw(mousePitch, mouseYaw, 0.0f); //Multiply difference by sensitivity, store in a quaternion
	XMStoreFloat4(&rotDeltaData, rotDelta);
	World::GetInstance()->m_mainCamera->GetOwner()->GetTransform()->SetRotation(rotDeltaData);
	
	if (prevMousePos.x != cursorPos.x || prevMousePos.y != cursorPos.y)
		printf((std::to_string(mouseYaw) + " " + std::to_string(mousePitch) + "\n").c_str());


	// Save position for next frame
	/*prevMousePos.x = cursorPos.x;
	prevMousePos.y = cursorPos.y;*/

	
	// Set cursor to center
	RECT windowRect;
	GetWindowRect(this->hWnd, &windowRect);
	int windowWidth = windowRect.right - windowRect.left;
	int windowHeight = windowRect.bottom - windowRect.top;
	SetCursorPos(windowRect.left + windowWidth / 2, windowRect.top + windowHeight / 2);

	prevMousePos.x = windowRect.left + windowWidth / 2;
	prevMousePos.y = windowRect.top + windowHeight / 2;

	//Confine mouse to window
	//GetClientRect(hWnd, &rect);
	//END MOUSE MOVEMENT

	////Calculate points 
	//POINT ul;
	//ul.x = rect.left;
	//ul.y = rect.top;

	//POINT rl;
	//rl.x = rect.right;
	//rl.y = rect.bottom;

	//MapWindowPoints(hWnd, nullptr, &ul, 1);
	//MapWindowPoints(hWnd, nullptr, &rl, 1);

	//rect.left = ul.x;
	//rect.top = ul.y;

	//rect.right = rl.x;
	//rect.bottom = rl.y;

	//ClipCursor(&rect);

	// Quit if the escape key is pressed
	if (GetAsyncKeyState(VK_ESCAPE))
		Quit();

	World::GetInstance()->Tick(deltaTime);
}

// --------------------------------------------------------
// Clear the screen, redraw everything, present to the user
// --------------------------------------------------------
void Game::Draw(float deltaTime, float totalTime)
{
	// Background color (Cornflower Blue in this case) for clearing
	const float color[4] = { 0.4f, 0.6f, 0.75f, 0.0f };

	// Clear the render target and depth buffer (erases what's on the screen)
	//  - Do this ONCE PER FRAME
	//  - At the beginning of Draw (before drawing *anything*)
	context->ClearRenderTargetView(backBufferRTV, color);
	context->ClearDepthStencilView(
		depthStencilView,
		D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL,
		1.0f,
		0);


	// Draw each entity
	World::GetInstance()->DrawEntities(context);

	



	// Present the back buffer to the user
	//  - Puts the final frame we're drawing into the window so the user can see it
	//  - Do this exactly ONCE PER FRAME (always at the very end of the frame)
	swapChain->Present(0, 0);

	// Due to the usage of a more sophisticated swap chain effect,
	// the render target must be re-bound after every call to Present()
	context->OMSetRenderTargets(1, &backBufferRTV, depthStencilView);
}


#pragma region Mouse Input

// --------------------------------------------------------
// Helper method for mouse clicking.  We get this information
// from the OS-level messages anyway, so these helpers have
// been created to provide basic mouse input if you want it.
// --------------------------------------------------------
void Game::OnMouseDown(WPARAM buttonState, int x, int y)
{
	// Add any custom code here...
	World::GetInstance()->OnMouseDown(buttonState, x, y);
	// Save the previous mouse position, so we have it for the future
	//prevMousePos.x = x;
	//prevMousePos.y = y;

	// Capture the mouse so we keep getting mouse move
	// events even if the mouse leaves the window.  we'll be
	// releasing the capture once a mouse button is released
	SetCapture(hWnd);
}

// --------------------------------------------------------
// Helper method for mouse release
// --------------------------------------------------------
void Game::OnMouseUp(WPARAM buttonState, int x, int y)
{
	// Add any custom code here...
	World::GetInstance()->OnMouseUp(buttonState, x, y);
	// We don't care about the tracking the cursor outside
	// the window anymore (we're not dragging if the mouse is up)
	ReleaseCapture();
}

// --------------------------------------------------------
// Helper method for mouse movement.  We only get this message
// if the mouse is currently over the window, or if we're 
// currently capturing the mouse.
// --------------------------------------------------------
void Game::OnMouseMove(WPARAM buttonState, int x, int y)
{
	// Save the previous mouse position, so we have it for the future

	//Lock Mouse to center of screen
	World::GetInstance()->OnMouseMove(buttonState, x, y);

	/*isTracking = false;

	RECT windowLoc;
	GetWindowRect(hWnd, &windowLoc);
	SetCursorPos(windowLoc.left + (width / 2), windowLoc.left + (height / 2));

	isTracking = true;*/


	//prevMousePos.x = x;
	//prevMousePos.y = y;
}

// --------------------------------------------------------
// Helper method for mouse wheel scrolling.  
// WheelDelta may be positive or negative, depending 
// on the direction of the scroll
// --------------------------------------------------------
void Game::OnMouseWheel(float wheelDelta, int x, int y)
{
	// Add any custom code here...
	World::GetInstance()->OnMouseWheel(wheelDelta, x, y);
}
#pragma endregion