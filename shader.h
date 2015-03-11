#ifndef MSHADER_H
#define MSHADER_H


class MShader
{
public:
	GLuint ProgramID;

	/// <summary>
	/// Creates a shader form a vsh and a fsh - places it in ProgramID
	/// </summary>
	void Create(std::string vertex_file_path, std::string fragment_file_path)
		{
			GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
			GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);


			std::string vertex_shader_code = "";
			std::ifstream vertex_shader_stream(vertex_file_path);
			if (vertex_shader_stream.is_open())
			{
				std::string line = "";
				while (getline(vertex_shader_stream, line)) {
					vertex_shader_code += line + "\n";
				}
				vertex_shader_stream.close();
			}

			std::string fragment_shader_code = "";
			std::ifstream fragment_shader_stream(fragment_file_path);
			if (fragment_shader_stream.is_open())
			{
				std::string line = "";
				while (getline(fragment_shader_stream, line)) {
					fragment_shader_code += line + "\n";
				}
				fragment_shader_stream.close();
			}


			GLint result = GL_FALSE;
			int info_log_length;


			std::cout << "Compiling shader: " << vertex_file_path;
			const char* vertex_source_pointer = vertex_shader_code.c_str();
			glShaderSource(VertexShaderID, 1, &vertex_source_pointer, NULL);
			glCompileShader(VertexShaderID);

			glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &result);
			glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &info_log_length);
			std::vector<char> vertex_shader_error_message(info_log_length);
			glGetShaderInfoLog(VertexShaderID, info_log_length, NULL, &vertex_shader_error_message[0]);
			std::cerr << &vertex_shader_error_message[0] << std::endl;


			std::cout << "Compiling shader: " << fragment_file_path;
			const char* fragment_source_pointer = fragment_shader_code.c_str();
			glShaderSource(FragmentShaderID, 1, &fragment_source_pointer, NULL);
			glCompileShader(FragmentShaderID);

			glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &result);
			glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &info_log_length);
			std::vector<char> fragment_shader_error_message(info_log_length);
			glGetShaderInfoLog(FragmentShaderID, info_log_length, NULL, &fragment_shader_error_message[0]);
			std::cerr << &fragment_shader_error_message[0] << std::endl;


			std::cout << "Linking program...";
			ProgramID = glCreateProgram();
			glAttachShader(ProgramID, VertexShaderID);
			glAttachShader(ProgramID, FragmentShaderID);
			glLinkProgram(ProgramID);

			glGetProgramiv(ProgramID, GL_LINK_STATUS, &result);
			glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &info_log_length);
			std::vector<char> program_error_message(std::max(info_log_length, 1));
			glGetProgramInfoLog(ProgramID, info_log_length, NULL, &program_error_message[0]);
			std::cerr << &program_error_message[0] << std::endl;
			std::cout << "[COMPLETE]\n" << std::endl;


			glDeleteShader(VertexShaderID);
			glDeleteShader(FragmentShaderID);
		}

	MShader(std::string vertex_file_path = "", std::string fragment_file_path = "") {
		if (vertex_file_path != "" && fragment_file_path != "") {
			Create(vertex_file_path, fragment_file_path);
		}
	}

	void Use() {
		glUseProgram(ProgramID);
	}
};


#endif