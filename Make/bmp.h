#ifndef BMP_H
#define BMP_H

#include <stdint.h>
/**
  \file
  \brief Заголовочный файл с описанием основных функция и структур для работы с файлами bmp.
*/

/**
  \brief Структура, содержащая информацию заголовков bmp файлов
*/
typedef struct _bmp_header {
    
    /* Данные файлового заголовка */
    /**
       \brief Отметка для отличя формата от других (сигнатура формата)
    */
    uint16_t signature;
    /**
       \brief Размер файла в байтах
    */
    uint32_t file_size;
    /**
       \brief Зарезервировано и содержит 0
    */
    uint16_t reserved1;
    /**
       \brief Зарезервировано и содержит 0
    */
    uint16_t reserved2;
    /**
       \brief Положение пискельных данных относительно начала данной структуры в байтах
    */
    uint32_t pixel_array_offset;
    
    /* Данные информационного заголовка */
    /**
       \brief Размер заголовка в байтах
    */
    uint32_t header_size;
    /**
       \brief Ширина растра в пикселях
    */
    int32_t width;
    /**
       \brief Высота растра в пикселях
    */
    int32_t height;
    /**
       \brief Поле для значков и курсоров Windows (для BMP всегда 1)
    */
    uint16_t color_planes;
    /**
       \brief Количество бит на пиксель
    */
    uint16_t bits_per_pixel;
    /**
       \brief Способо хранения пикселей
    */
    uint32_t compression_method;
    /**
       \brief Размер пиксельных данных в байтах 
    */
    uint32_t image_size;
    /**
       \brief Количесвто пикселей на метр по горизонтали
    */
    int32_t horizontal_resolution;
    /**
       \brief Количество пикселей на метр по вертикали
    */
    int32_t vertical_resolution;
    /**
       \brief Размер таблицы цветов в ячейках
    */
    uint32_t colors;
    /**
       \brief Количество ячеек от начала таблицы цветов до последней используемой
    */
    uint32_t important_colors;    
} bmp_header;

/**
   \brief Структура, содержащая массив пикселей изображения bmp
*/
typedef double *bmp_pixel_array;

/**
   \brief Структура, для хранения изображения bmp и информации о нём
*/
typedef struct _bmp_image {
    /**
       \brief Структура, для хранения информации заголовков изображения bmp
    */
    bmp_header header;
    /**
       \brief Структура, для хранения массива пикселей изображения bmp
    */
    bmp_pixel_array pixel_array;
} bmp_image;

bmp_image bmp_read(char *bmp_file_path);


void bmp_write(char *bmp_file_path, bmp_image image);

void bmp_motionblur(bmp_image image);

void bmp_rezko(bmp_image image);

#endif
