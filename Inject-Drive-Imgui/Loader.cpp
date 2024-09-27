/*
 * 版权所有 (c) [2024-09-27] [By:Codeant]
 *
 * https://discord.gg/Zg5t4Gc7wr
 *
 * 开源代码免责声明：
 *
 * 1. 本代码以“现状”提供，不作任何明示或暗示的担保，包括但不限于对适销性、适用于特定用途及无侵权的担保。
 *    The code is provided "as is," without warranty of any kind, express or implied,
 *    including but not limited to the warranties of merchantability, fitness for a
 *    particular purpose, and non-infringement.
 *
 * 2. 在任何情况下，作者或版权持有者均不对因使用本代码而产生的任何索赔、损害或其他责任负责，无论是在合同诉讼、
 *    侵权行为或其他情形下产生的责任。
 *    In no event shall the author or copyright holders be liable for any claim,
 *    damages, or other liability, whether in an action of contract, tort, or otherwise,
 *    arising from, out of, or in connection with the software or the use or other
 *    dealings in the software.
 *
 * 3. 用户应自行承担使用本代码的风险，作者不承担因使用或无法使用本代码所引起的任何直接、间接、特殊、偶然或
 *    后果性损害。
 *    Users shall assume all risks associated with using the code. The author is not
 *    liable for any direct, indirect, special, incidental, or consequential damages
 *    arising from the use or inability to use the code.
 *
 * 4. 本代码可能会包含第三方开源代码的引用或链接，使用这些第三方代码需遵守其各自的许可协议。
 *    This code may contain references or links to third-party open-source code, which
 *    must be used in accordance with their respective license agreements.
 *
 * 5. 使用本代码即表示您同意本免责声明的所有条款。
 *    By using this code, you agree to all the terms outlined in this disclaimer.
 *
 */

#pragma once
#include "Loader.hpp"
#include "auth.hpp"
#include <comdef.h>
#pragma execution_character_set("utf-8")

int client_width;
int client_height;

static int default_route = 0;
static int input_box_size = 150;

bool member_login = false;
bool show_demo_window = true;

std::string hint_text_info = "";
std::string hint_announcement_info = "";
static char please_enter_account[256] = "";

inline char* KS_ANSI_to_UTF8(const char* szAnsi)
{
    if (szAnsi == NULL)
        return NULL;

    _bstr_t   bstrTmp(szAnsi);
    int       nLen = ::WideCharToMultiByte(CP_UTF8, 0, (LPCWSTR)bstrTmp, -1, NULL, 0, NULL, NULL);
    char* pUTF8 = new char[nLen + 1];
    ZeroMemory(pUTF8, nLen + 1);
    ::WideCharToMultiByte(CP_UTF8, 0, (LPCWSTR)bstrTmp, -1, pUTF8, nLen, NULL, NULL);
    return pUTF8;
}

namespace Settings
{
    static int Tab = 1;
}

void ShowDemoUI()
{
    auto& style = ImGui::GetStyle();
    style.FramePadding = { 8.f, 5.f };
    style.WindowTitleAlign = { 0.0f, 0.5f }; // Center title
    style.ButtonTextAlign = { 0.5f, 0.5f };  // Button text centered
    style.DisplaySafeAreaPadding = { 3.f, 3.f };

    auto& colors = style.Colors;
    colors[ImGuiCol_Text] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f); // Text color
    colors[ImGuiCol_WindowBg] = ImVec4(0.94f, 0.94f, 0.94f, 1.00f); // Window background color
    colors[ImGuiCol_PopupBg] = ImVec4(1.00f, 1.00f, 1.00f, 0.98f);
    colors[ImGuiCol_Border] = ImVec4(0.00f, 0.00f, 0.00f, 0.30f);
    colors[ImGuiCol_FrameBg] = ImColor(255, 255, 255, 100); // Default input box color
    colors[ImGuiCol_FrameBgActive] = ImVec4(0.28f, 0.27f, 0.27f, 0.54f); // Input box hover color
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.21f, 0.21f, 0.21f, 0.78f); // Input box active color
    colors[ImGuiCol_TitleBg] = ImColor(255, 255, 255, 255); // Window default color
    colors[ImGuiCol_TitleBgActive] = ImColor(255, 255, 255, 255); // Window bar hover color
    colors[ImGuiCol_TitleBgCollapsed] = ImColor(255, 255, 255, 255); // Window bar active color
    colors[ImGuiCol_Button] = ImColor(0, 191, 255, 255); // Button default color
    colors[ImGuiCol_ButtonHovered] = ImColor(0, 191, 255, 200); // Button hover color
    colors[ImGuiCol_ButtonActive] = ImColor(220, 20, 60, 255); // Button active color
    colors[ImGuiCol_Tab] = ImColor(255, 255, 255, 255); // Tab default color
    colors[ImGuiCol_TabHovered] = ImColor(0, 191, 255, 100); // Tab hover color
    colors[ImGuiCol_TabActive] = ImColor(0, 191, 255, 255); // Tab active color
}

void LoginDemo()
{
    ImGui::Text("");
    ImGui::Text("DLL"); ImGui::SameLine();
    ImGui::SetNextItemWidth(input_box_size);
    ImGui::InputText("##", please_enter_account, IM_ARRAYSIZE(please_enter_account));

    ImGui::Text(" "); ImGui::SameLine();
    static ImVec4 active = imguipp::to_vec4(255, 255, 255, 255);
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, active);

    ImGui::NewLine();
    if (ImGui::Button("Inject", ImVec2(input_box_size + 30, 35)))
    {
        if (member_login)
        {
            hint_text_info = Codeant::InjectDriverModule("Grand Theft Auto V", please_enter_account);
        }
    }
}

void ShowDemo(bool* p_open)
{
    ShowDemoUI();

    ImGuiWindowFlags window_flags = 0;
    window_flags |= ImGuiWindowFlags_NoCollapse;
    window_flags |= ImGuiWindowFlags_NoResize;
    window_flags |= ImGuiWindowFlags_NoScrollbar;

    ImGui::SetNextWindowPos(ImVec2((client_width / 2) - (200 / 2), (client_height / 2) - (170 / 2)), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(200, 170), ImGuiCond_FirstUseEver);

    if (!ImGui::Begin("Dll Inject By:Codeant", p_open, window_flags))
    {
        ImGui::End();
        return;
    }
    ImGui::PushItemWidth(ImGui::GetFontSize() * -12);

    LoginDemo();

    ImGui::SetCursorPosY(ImGui::GetWindowHeight() - 25);
    imguipp::center_text_ex(hint_text_info.c_str(), 10, 1, false);

    ImGui::PopItemWidth();
    ImGui::End();
}

bool isWin7()
{
    OSVERSIONINFOEX osvi;
    BOOL bOsVersionInfoEx;

    ZeroMemory(&osvi, sizeof(OSVERSIONINFOEX));
    osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
    bOsVersionInfoEx = GetVersionEx((OSVERSIONINFO*)&osvi);

    // Windows 7 system version is NT6.1
    if (VER_PLATFORM_WIN32_NT == osvi.dwPlatformId &&
        osvi.dwMajorVersion == 6 &&
        osvi.dwMinorVersion == 1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

static bool Enabled = true;
HWND Window = nullptr;

LPDIRECT3DDEVICE9        g_pd3dDevice;
D3DPRESENT_PARAMETERS    g_d3dpp;
LPDIRECT3D9              g_pD3D;

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

const int WINDOW_WIDTH = 1200;
const int WINDOW_HEIGHT = 800;

bool CreateDeviceD3D(HWND hWnd)
{
    if ((g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)) == NULL)
        return false;
    ZeroMemory(&g_d3dpp, sizeof(g_d3dpp));
    g_d3dpp.Windowed = TRUE;
    g_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    g_d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
    g_d3dpp.EnableAutoDepthStencil = TRUE;
    g_d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
    g_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
    if (g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &g_d3dpp, &g_pd3dDevice) < 0)
        return false;
    return true;
}

void CleanupDeviceD3D()
{
    if (g_pd3dDevice) {
        g_pd3dDevice->Release(); g_pd3dDevice = NULL;
    }
    if (g_pD3D) {
        g_pD3D->Release(); g_pD3D = NULL;
    }
}

void ResetDevice()
{
    ImGui_ImplDX9_InvalidateDeviceObjects();
    HRESULT Result = g_pd3dDevice->Reset(&g_d3dpp);
    if (Result == D3DERR_INVALIDCALL)
        IM_ASSERT(0);
    ImGui_ImplDX9_CreateDeviceObjects();
}

DWORD WINAPI ThreadFun2(LPVOID lpParameter)
{
    member_login = true;

    return 0;
}

DWORD WINAPI ThreadFun1(LPVOID lpParameter)
{
    WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandleA(0), 0,0,0, 0, "Dll Inject", 0 };
    RegisterClassEx(&wc);
    Window = CreateWindow(wc.lpszClassName, "Dll Inject", WS_POPUP, 0, 0, 5, 5, 0, 0, wc.hInstance, 0);

    // Always keep the window on top
    SetWindowPos(Window, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);

    if (!CreateDeviceD3D(Window))
    {
        CleanupDeviceD3D();
        UnregisterClass(wc.lpszClassName, wc.hInstance);
        return 1;
    }

    ShowWindow(Window, SW_HIDE);
    UpdateWindow(Window);

    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO();

    if (isWin7())
    {
        io.Fonts->AddFontFromFileTTF("c:/windows/fonts/msyh.ttf", 15.0f, NULL, io.Fonts->GetGlyphRangesChineseFull());
    }
    else
    {
        io.Fonts->AddFontFromFileTTF("c:/windows/fonts/msyh.ttc", 15.0f, NULL, io.Fonts->GetGlyphRangesChineseFull());
    }

    HWND hd = GetDesktopWindow();
    // Method 1
    RECT rect;
    // Only get the size of the client area of the window
    GetClientRect(hd, &rect);
    client_width = (rect.right - rect.left);
    client_height = (rect.bottom - rect.top);

    io.IniFilename = nullptr;
    io.LogFilename = nullptr;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    static const ImWchar icons_ranges[] = { 0xf000, 0xf3ff, 0 };
    ImFontConfig icons_config;

    io.IniFilename = nullptr;
    io.LogFilename = nullptr;

    icons_config.MergeMode = true;
    icons_config.PixelSnapH = true;
    icons_config.OversampleH = 3;
    icons_config.OversampleV = 3;

    ImFontConfig CustomFont;
    CustomFont.FontDataOwnedByAtlas = false;

    ImGui_ImplWin32_Init(Window);
    ImGui_ImplDX9_Init(g_pd3dDevice);

    MSG msg;
    memset(&msg, 0, sizeof(msg));
    while (msg.message != WM_QUIT)
    {
        if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
            continue;
        }

        ImGui_ImplDX9_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        if (show_demo_window)
        {
            ShowDemo(&show_demo_window);
        }
        else
        {
            ExitProcess(0);
        }

        // Rendering
        ImGui::EndFrame();

        g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0, 1.0f, 0);
        if (g_pd3dDevice->BeginScene() >= 0)
        {
            ImGui::Render();
            ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
            g_pd3dDevice->EndScene();
        }

        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
        }

        HRESULT result = g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
        if (result == D3DERR_DEVICELOST && g_pd3dDevice->TestCooperativeLevel() == D3DERR_DEVICENOTRESET) {
            ResetDevice();
        }
        if (!Enabled) {
            msg.message = WM_QUIT;
        }
    }

    ImGui_ImplDX9_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    CleanupDeviceD3D();
    DestroyWindow(Window);
    UnregisterClass(wc.lpszClassName, wc.hInstance);

    return 0;
}

int APIENTRY WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    HANDLE hThread2 = CreateThread(NULL, 0, ThreadFun2, NULL, 0, NULL);
    WaitForSingleObject(hThread2, INFINITE); // Wait for the thread

    HANDLE hThread1 = CreateThread(NULL, 0, ThreadFun1, NULL, 0, NULL);
    WaitForSingleObject(hThread1, INFINITE); // Wait for the thread

    return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;

    switch (msg)
    {
    case WM_SIZE:
        if (g_pd3dDevice != NULL && wParam != SIZE_MINIMIZED)
        {
            g_d3dpp.BackBufferWidth = LOWORD(lParam);
            g_d3dpp.BackBufferHeight = HIWORD(lParam);
            ResetDevice();
        }
        return 0;
    case WM_SYSCOMMAND:
        if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
            return 0;
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hWnd, msg, wParam, lParam);
}
