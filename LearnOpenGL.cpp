#include<glad\glad.h>
#include<GLFW/glfw3.h>
#include<iostream>

float vertices[] = {
	-0.5f,-0.5,0.0f,//left
	0.5f,-0.5,0.0f,//right
	0.0f,0.5f,0.0f//top
};
GLFWwindow* window;//����ָ��
int shaderProgram;//��������ķ���ֵ


void VAOSet() {
	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	//���Կ�дֵ�������Դ�ռ�GL_STATIC_DRAW��ʾֵ���޸�
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}

void init() {
	//��ʼ��
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
	//��Դ������ַ���
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
	int vertexShader = glCreateShader(GL_VERTEX_SHADER);//������ɫ������
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);//��Դ��
	glCompileShader(vertexShader);//������ɫ������

	int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);//������ɫ������
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);//��Դ��
	glCompileShader(fragmentShader);//������ɫ������

	shaderProgram = glCreateProgram();//��������
	glAttachShader(shaderProgram, vertexShader);//������ɫ������
	glAttachShader(shaderProgram, fragmentShader);//������ɫ������
	glLinkProgram(shaderProgram);//�������ɳ���
}

int main() 
{
	init();
	VAOSet();
	shaderSet();
	//��Ⱦ����
	
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shaderProgram);//ʹ�ó���
		glDrawArrays(GL_TRIANGLES, 0,3);//������
		glfwPollEvents();
		glfwSwapBuffers(window);
	}
	//�˳�
	glfwTerminate();

	return 0;
}