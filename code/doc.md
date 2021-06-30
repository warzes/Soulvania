
ƒиздок по идее 2д соула метроинвадии в стиле
https://dtf.ru/indie/779409-2d-ekshen-platformer-s-krovushkoy-i-pikselyami (и ссылок из комментов)
tomb of the mask

https://github.com/NearHuscarl/Castlevania


- base::Color удалить и использовать raylib::Color
- base::Vector2 удалить и использовать raylib::Vector2
- вообще удал€ть все лишнее
- в том числе и из рейлиба и зависимостей


идеи дл€ рейлиба
	в заголовке core.c удалить glfw window
	добавить функцию отрисовки части текстуры с масштабом и вращением


Commits on Jun 28, 2021
	Update uwp_events.h
	@raysan5
	raysan5 committed 11 hours ago

		в raylib добавил 
			#define PLATFORM_DESKTOP 1
			#define GRAPHICS_API_OPENGL_33 1

		в конфиге рейлиба
			отключить
				SUPPORT_CAMERA_SYSTEM (сво€ камера, но может потом проверить)
				SUPPORT_GESTURES_SYSTEM 
				SUPPORT_MOUSE_GESTURES
				SUPPORT_SSH_KEYBOARD_RPI (хер знает зачем оно)
				SUPPORT_COMPRESSION_API (пока не используетс€)
				SUPPORT_DATA_STORAGE (пока не используетс€)
				SUPPORT_FILEFORMAT_DDS
				SUPPORT_FILEFORMAT_HDR
				SUPPORT_FILEFORMAT_OBJ SUPPORT_FILEFORMAT_MTL SUPPORT_FILEFORMAT_IQM SUPPORT_FILEFORMAT_GLTF SUPPORT_MESH_GENERATION - не использую 3д, поэтому и этот код не нужен
			включить
				SUPPORT_GIF_RECORDING (запись гифки по ctrl-f12)
				SUPPORT_FILEFORMAT_BMP

glfw
	Commits on Jun 26, 2021
		Remove errors for gamepad element mismatch Е
