
������ �� ���� 2� ����� ������������ � �����
https://dtf.ru/indie/779409-2d-ekshen-platformer-s-krovushkoy-i-pikselyami (� ������ �� ���������)
tomb of the mask

https://github.com/NearHuscarl/Castlevania


- base::Color ������� � ������������ raylib::Color
- base::Vector2 ������� � ������������ raylib::Vector2
- ������ ������� ��� ������
- � ��� ����� � �� ������� � ������������


���� ��� �������
	� ��������� core.c ������� glfw window
	�������� ������� ��������� ����� �������� � ��������� � ���������


Commits on Jun 28, 2021
	Update uwp_events.h
	@raysan5
	raysan5 committed 11 hours ago

		� raylib ������� 
			#define PLATFORM_DESKTOP 1
			#define GRAPHICS_API_OPENGL_33 1

		� ������� �������
			���������
				SUPPORT_CAMERA_SYSTEM (���� ������, �� ����� ����� ���������)
				SUPPORT_GESTURES_SYSTEM 
				SUPPORT_MOUSE_GESTURES
				SUPPORT_SSH_KEYBOARD_RPI (��� ����� ����� ���)
				SUPPORT_COMPRESSION_API (���� �� ������������)
				SUPPORT_DATA_STORAGE (���� �� ������������)
				SUPPORT_FILEFORMAT_DDS
				SUPPORT_FILEFORMAT_HDR
				SUPPORT_FILEFORMAT_OBJ SUPPORT_FILEFORMAT_MTL SUPPORT_FILEFORMAT_IQM SUPPORT_FILEFORMAT_GLTF SUPPORT_MESH_GENERATION - �� ��������� 3�, ������� � ���� ��� �� �����
			��������
				SUPPORT_GIF_RECORDING (������ ����� �� ctrl-f12)
				SUPPORT_FILEFORMAT_BMP

glfw
	Commits on Jun 26, 2021
		Remove errors for gamepad element mismatch �
