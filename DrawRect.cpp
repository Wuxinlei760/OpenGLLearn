#include<glad\glad.h>
#include<GLFW/glfw3.h>
#include<iostream>

float vertices[] = {
	0.5f, 0.5f, 0.0f,   // 右上角
	0.5f, -0.5f, 0.0f,  // 右下角
	-0.5f, -0.5f, 0.0f, // 左下角
	-0.5f, 0.5f, 0.0f   // 左上角
};
unsigned int indices[] = { // 注意索引从0开始! 
	0, 1, 3, // 第一个三角形
	1, 2, 3  // 第二个三角形
};
GLFWwindow* window;//窗口指针
int shaderProgram;//创建程序的返回值
unsigned int VBO, VAO, EBO;


void VAOSet() {
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	// 1. 绑定顶点数组对象
	glBindVertexArray(VAO);
	// 2. 把我们的顶点数组复制到一个顶点缓冲中，供OpenGL使用
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// 3. 复制我们的索引数组到一个索引缓冲中，供OpenGL使用
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	// 4. 设定顶点属性指针
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
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
		"gl_Position = vec4(aPos.x,aPos.y, aPos.z, 1.0f);\n"
		"}\n\0";

	const char* fragmentShaderSource = "#version 400 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"}\n\0";
	/*顶点着色器的生成*/
	int vertexShader = glCreateShader(GL_VERTEX_SHADER);//创建着色器对象
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);//绑定源码
	glCompileShader(vertexShader);//编译着色器对象
	int  success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);//检测编译是否成功
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);//获取错误消息
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	/*片段着色器的生成*/
	int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);//创建着色器对象
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);//绑定源码
	glCompileShader(fragmentShader);//编译着色器对象
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);//检测编译是否成功
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);//获取错误消息
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	shaderProgram = glCreateProgram();//创建程序
	glAttachShader(shaderProgram, vertexShader);//附加定点着色器对象
	glAttachShader(shaderProgram, fragmentShader);//附加片段着色器对象
	glLinkProgram(shaderProgram);//链接生成程序
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::LINK_FAILED\n" << infoLog << std::endl;
	}
}
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

int main() 
{
	init();
	VAOSet();
	shaderSet();
	//渲染引擎
	
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		//glDrawArrays(GL_TRIANGLES, 0, 3);//画三角
		glfwPollEvents();
		glfwSwapBuffers(window);
	}
	//退出
	glfwTerminate();

	return 0;
}