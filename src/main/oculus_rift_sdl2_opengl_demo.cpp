/*
 * Comes from here: https://pastebin.com/hGHRG9Xx
 * */

#define GLEW_STATIC
#include "GL/glew.h"
// Uncomment your platform
//#define OVR_OS_WIN32
//#define OVR_OS_MAC
//#define OVR_OS_LINUX
#include "OVR_CAPI_GL.h"
#include "Kernel/OVR_Math.h"
#include "SDL.h"
#include "SDL_syswm.h"

using namespace OVR;

int main(int argc, char *argv[])
{
	SDL_Init(SDL_INIT_VIDEO);

	int x = SDL_WINDOWPOS_CENTERED;
	int y = SDL_WINDOWPOS_CENTERED;
	Uint32 flags = SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN;

	bool debug = false;

	ovr_Initialize();

	ovrHmd hmd = ovrHmd_Create(0);

	if (hmd == NULL)
	{
		hmd = ovrHmd_CreateDebug(ovrHmd_DK1);

		debug = true;
	}

	ovrHmdDesc hmdDesc;

	ovrHmd_GetDesc(hmd, &hmdDesc);

	if (debug == false)
	{
		x = hmdDesc.WindowsPos.x;
		y = hmdDesc.WindowsPos.y;
		flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
	}

	int w = hmdDesc.Resolution.w;
	int h = hmdDesc.Resolution.h;

	SDL_Window *window = SDL_CreateWindow("Oculus Rift SDL2 OpenGL Demo", x, y, w, h, flags);

	SDL_GLContext context = SDL_GL_CreateContext(window);

	glewExperimental = GL_TRUE;

	glewInit();

	Sizei recommendedTex0Size = ovrHmd_GetFovTextureSize(hmd, ovrEye_Left, hmdDesc.DefaultEyeFov[0], 1.0f);
	Sizei recommendedTex1Size = ovrHmd_GetFovTextureSize(hmd, ovrEye_Right, hmdDesc.DefaultEyeFov[1], 1.0f);
	Sizei renderTargetSize;
	renderTargetSize.w = recommendedTex0Size.w + recommendedTex1Size.w;
	renderTargetSize.h = max(recommendedTex0Size.h, recommendedTex1Size.h);

	GLuint frameBuffer;
	glGenFramebuffers(1, &frameBuffer);
	
	GLuint texture;
	glGenTextures(1, &texture);

	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, renderTargetSize.w, renderTargetSize.h, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, texture, 0);

	GLuint renderBuffer;
	glGenRenderbuffers(1, &renderBuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, renderBuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, renderTargetSize.w, renderTargetSize.h);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, renderBuffer);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		glDeleteFramebuffers(1, &frameBuffer);
		glDeleteTextures(1, &texture);
		glDeleteRenderbuffers(1, &renderBuffer);

		SDL_GL_DeleteContext(context);

		SDL_DestroyWindow(window);

		ovrHmd_Destroy(hmd);

		ovr_Shutdown();

		SDL_Quit();

		return 0;
	}

	ovrFovPort eyeFov[2] = { hmdDesc.DefaultEyeFov[0], hmdDesc.DefaultEyeFov[1] };

	ovrRecti eyeRenderViewport[2];
	eyeRenderViewport[0].Pos = Vector2i(0, 0);
	eyeRenderViewport[0].Size = Sizei(renderTargetSize.w / 2, renderTargetSize.h);
	eyeRenderViewport[1].Pos = Vector2i((renderTargetSize.w + 1) / 2, 0);
	eyeRenderViewport[1].Size = eyeRenderViewport[0].Size;

	ovrGLTexture eyeTexture[2];
	eyeTexture[0].OGL.Header.API = ovrRenderAPI_OpenGL;
	eyeTexture[0].OGL.Header.TextureSize = renderTargetSize;
	eyeTexture[0].OGL.Header.RenderViewport = eyeRenderViewport[0];
	eyeTexture[0].OGL.TexId = texture;

	eyeTexture[1] = eyeTexture[0];
	eyeTexture[1].OGL.Header.RenderViewport = eyeRenderViewport[1];

	SDL_SysWMinfo info;

	SDL_VERSION(&info.version);

	SDL_GetWindowWMInfo(window, &info);

	ovrGLConfig cfg;
	cfg.OGL.Header.API = ovrRenderAPI_OpenGL;
	cfg.OGL.Header.RTSize = Sizei(hmdDesc.Resolution.w, hmdDesc.Resolution.h);
	cfg.OGL.Header.Multisample = 1;
#if defined(OVR_OS_WIN32)
	cfg.OGL.Window = info.info.win.window;
#elif defined(OVR_OS_LINUX)
	cfg.OGL.Disp = info.info.x11.display;
	cfg.OGL.Win = info.info.x11.window;
#endif

	ovrEyeRenderDesc eyeRenderDesc[2];

	ovrHmd_ConfigureRendering(hmd, &cfg.Config, ovrDistortionCap_Chromatic | ovrDistortionCap_TimeWarp, eyeFov, eyeRenderDesc);

	ovrHmd_SetEnabledCaps(hmd, ovrHmdCap_LowPersistence | ovrHmdCap_LatencyTest);

	ovrHmd_StartSensor(hmd, ovrSensorCap_Orientation | ovrSensorCap_YawCorrection | ovrSensorCap_Position, 0);

	const GLchar *vertexShaderSource[] = {
		"#version 150\n"
		"uniform mat4 MVPMatrix;\n"
		"in vec3 position;\n"
		"void main()\n"
		"{\n"
		"    gl_Position = MVPMatrix * vec4(position, 1.0);\n"
		"}"
	};

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, vertexShaderSource, 0);
	glCompileShader(vertexShader);

	const GLchar *fragmentShaderSource[] = {
		"#version 150\n"
		"out vec4 outputColor;\n"
		"void main()\n"
		"{\n"
		"    outputColor = vec4(1.0, 0.0, 0.0, 1.0);\n"
		"}"
	};

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, fragmentShaderSource, 0);
	glCompileShader(fragmentShader);

	GLuint program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);
	glUseProgram(program);

	GLuint MVPMatrixLocation = glGetUniformLocation(program, "MVPMatrix");
	GLuint positionLocation = glGetAttribLocation(program, "position");

	GLuint vertexArray;
	glGenVertexArrays(1, &vertexArray);
	glBindVertexArray(vertexArray);

	GLfloat vertices[] = {
		0.0f, 1.0f, -2.0f,
		-1.0f, -1.0f, -2.0f,
		1.0f, -1.0f, -2.0f
	};

	GLuint positionBuffer;
	glGenBuffers(1, &positionBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(positionLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(positionLocation);

	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
	glClearDepth(1.0f);

	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);

	bool running = true;

	while (running)
	{
		SDL_Event event;

		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				running = false;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					running = false;
					break;
				default:
					break;
				}
				break;
			default:
				break;
			}
		}

		ovrFrameTiming frameTiming = ovrHmd_BeginFrame(hmd, 0);

		glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		ovrPosef eyeRenderPose[2];

		for (int eyeIndex = 0; eyeIndex < ovrEye_Count; eyeIndex++)
		{
			ovrEyeType eye = hmdDesc.EyeRenderOrder[eyeIndex];
			eyeRenderPose[eye] = ovrHmd_BeginEyeRender(hmd, eye);

			Matrix4f MVPMatrix = Matrix4f(ovrMatrix4f_Projection(eyeRenderDesc[eye].Fov, 0.01f, 10000.0f, true)) * Matrix4f::Translation(eyeRenderDesc[eye].ViewAdjust) * Matrix4f(Quatf(eyeRenderPose[eye].Orientation).Inverted());

			glUniformMatrix4fv(MVPMatrixLocation, 1, GL_FALSE, &MVPMatrix.Transposed().M[0][0]);

			glViewport(eyeRenderViewport[eye].Pos.x, eyeRenderViewport[eye].Pos.y, eyeRenderViewport[eye].Size.w, eyeRenderViewport[eye].Size.h);

			glDrawArrays(GL_TRIANGLES, 0, 3);

			ovrHmd_EndEyeRender(hmd, eye, eyeRenderPose[eye], &eyeTexture[eye].Texture);
		}

		ovrHmd_EndFrame(hmd);
	}

	glDeleteVertexArrays(1, &vertexArray);
	glDeleteBuffers(1, &positionBuffer);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	glDeleteProgram(program);

	glDeleteFramebuffers(1, &frameBuffer);
	glDeleteTextures(1, &texture);
	glDeleteRenderbuffers(1, &renderBuffer);

	SDL_GL_DeleteContext(context);

	SDL_DestroyWindow(window);

	ovrHmd_Destroy(hmd);

	ovr_Shutdown();

	SDL_Quit();

	return 0;
}
