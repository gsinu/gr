#include <windows.h>
#include <gl/GL.h>
#pragma comment(lib, "opengl32.lib")

float r = 0;

// 1. OpenGL 초기화: 윈도우와 그래픽 카드를 연결
void InitGL(HWND hwnd, HDC hdc) {
    PIXELFORMATDESCRIPTOR p = { sizeof(p), 1, PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,NULL , 32 };
    SetPixelFormat(hdc, ChoosePixelFormat(hdc, &p), &p);
    wglMakeCurrent(hdc, wglCreateContext(hdc));
}

// 2. 그리기 루틴: 회전 및 무지개 삼각형 정의
void Draw() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glRotatef(r += 0.05f, 0, 0, 1);

    glBegin(GL_TRIANGLES);
    glColor3f(1, 0, 0); glVertex2f(0, 0.5);   // 빨강
    glColor3f(0, 1, 0); glVertex2f(0.5, -0.5); // 초록
    glColor3f(0, 0, 1); glVertex2f(-0.5, -0.5);// 파랑
    glEnd();
}

// 3. 메시지 처리 및 메인 루프
LRESULT CALLBACK WndProc(HWND h, UINT m, WPARAM w, LPARAM l) {
    if (m == WM_DESTROY) PostQuitMessage(0);
    return DefWindowProc(h, m, w, l);
}

int main() {
    HINSTANCE hI = GetModuleHandle(0);
    WNDCLASS wc = { 0, WndProc, 0, 0, hI, 0, 0, 0, 0, L"GL" };
    RegisterClass(&wc);

    HWND hwnd = CreateWindow(L"GL", L"A", WS_VISIBLE | WS_OVERLAPPEDWINDOW, 0, 0, 500, 500, 0, 0, hI, 0);
    HDC hdc = GetDC(hwnd);
    InitGL(hwnd, hdc);

    MSG msg;
    while (1) {
        if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT) break;
            DispatchMessage(&msg);
        }
        else {
            Draw();
            SwapBuffers(hdc);
        }
    }
    return 0;
}