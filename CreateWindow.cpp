#include<glad\glad.h>
#include<GLFW/glfw3.h>
#include<iostream>

void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

int main()
{
	//初始化GLFW窗口
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//设置主版本
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);//设置次版本
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//设置OpenGL是核心模式

	//创建窗口
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);//设置窗口长宽以及名字，后面两个参数暂不理
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);//设置该窗口的上下文为当前线程的主上下文

	//初始化GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	//定义OpenGL渲染窗口的尺寸大小 参数（左下角x坐标，左下角y坐标，长，宽）
	glViewport(0, 0, 800, 600);

	//渲染
	while (!glfwWindowShouldClose(window))
	{
		//输入
		processInput(window);

		//渲染指令
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//检查并调用时间，并交换缓冲
		glfwSwapBuffers(window); //交换颜色缓冲，可以理解为刷新
		glfwPollEvents();//函数检查有没有出发什么事件
	}

	//释放所有申请的资源
	glfwTerminate();

	return 0;
}