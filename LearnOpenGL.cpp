#include<glad\glad.h>
#include<GLFW/glfw3.h>
#include<iostream>

float vertices[] = {
	-0.5f,-0.5,0.0f,//left
	0.5f,-0.5,0.0f,//right
	0.0f,0.5f,0.0f//top
};
GLFWwindow* window;//窗口指针
int shaderProgram;//创建程序的返回值


void VAOSet() {
	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	//往显卡写值，分配显存空间GL_STATIC_DRAW表示值不修改
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}

void init() {
	//初始化
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(800, 600, "OPENGL", NULL, NULL);
	if (!window) {
		printf("err:windows is NULL");
		glfwTerminate();
		return ;
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		printf("err:windows is NULL");
		return ;
	}
}
void shaderSet() {
	//将源码存入字符串
	const char* vertexShaderSource = "#version 400 core\n"
		"layout(location=0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"gl_Position = vec4(aPos.x+0.5,aPos.y, aPos.z, 1.0f);\n"
		"}\n\0";

	const char* fragmentShaderSource = "#version 400 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"}\n\0";
	int vertexShader = glCreateShader(GL_VERTEX_SHADER);//创建着色器对象
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);//绑定源码
	glCompileShader(vertexShader);//编译着色器对象

	int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);//创建着色器对象
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);//绑定源码
	glCompileShader(fragmentShader);//编译着色器对象

	shaderProgram = glCreateProgram();//创建程序
	glAttachShader(shaderProgram, vertexShader);//附加着色器对象
	glAttachShader(shaderProgram, fragmentShader);//附加着色器对象
	glLinkProgram(shaderProgram);//链接生成程序
}

int main() 
{
	init();
	VAOSet();
	shaderSet();
	//渲染引擎
	
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shaderProgram);//使用程序
		glDrawArrays(GL_TRIANGLES, 0,3);//画三角
		glfwPollEvents();
		glfwSwapBuffers(window);
	}
	//退出
	glfwTerminate();

	return 0;
}