#ifndef _APP_H_
#define _APP_H_
#include <windows.h>
#include <d3d11_1.h>
#include <directxcolors.h>
#include "resource.h"

#include <WinSDKVer.h>
#define _WIN32_WINNT 0x0602
#include <SDKDDKVer.h>

//=================================================================
// All Application and DirectX base level stuff goes here
//=================================================================

using namespace DirectX;

class Game;

class Application
{
public:
	Application () {};
	~Application() { CleanupDevice(); };

	//init the Windows window and the game
	HRESULT InitWindow(HINSTANCE _hInstance, int _nCmdShow);

	//init and tidy up after use DirectX resources
	HRESULT InitDevice();
	void CleanupDevice(); //also deletes current game

						  //tick and render the app and game
	bool Update();
	void Render();

protected:

	//Window handles
	HINSTANCE               m_hInst = nullptr;
	HWND                    m_hWnd = nullptr;

	//DirectX Resources
	D3D_DRIVER_TYPE         m_driverType = D3D_DRIVER_TYPE_NULL;
	D3D_FEATURE_LEVEL       m_featureLevel = D3D_FEATURE_LEVEL_11_0;
	ID3D11Device*           m_pd3dDevice = nullptr;
	ID3D11Device1*          m_pd3dDevice1 = nullptr;
	ID3D11DeviceContext*    m_pImmediateContext = nullptr;
	ID3D11DeviceContext1*   m_pImmediateContext1 = nullptr;
	IDXGISwapChain*         m_pSwapChain = nullptr;
	IDXGISwapChain1*        m_pSwapChain1 = nullptr;
	ID3D11RenderTargetView* m_pRenderTargetView = nullptr;
	ID3D11Texture2D*        m_pDepthStencil = nullptr;
	ID3D11DepthStencilView* m_pDepthStencilView = nullptr;
	ID3D11RasterizerState*  m_pRasterState = nullptr;

	float m_ClearColour[4];

	//pointer to current game
	Game*					m_Game = nullptr;
};

#endif