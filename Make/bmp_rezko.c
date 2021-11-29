#include "bmp.h"
#include "stdlib.h"
#include <stdio.h>
/**
* @file
* @brief Фильтр усиления резкости
* @param image Исходное изображение класса bmp_image.
*
*/

void mprove(double *a, unsigned int w, unsigned h,bmp_image image);

/**
* @brief Функция реализующая фильтр усиления резкости
* @param image Исходное изображение класса bmp_image.
*
*/
void bmp_rezko(bmp_image image)
{
    unsigned int i, j;

    /* Получаем линейные размеры изображения */
    unsigned int w = image.header.width;
    unsigned int h = image.header.height;    

    /* Создание расширенного изображения */
    double *b;
    b = (double*) malloc (sizeof (double) * h * w * 3);
    mprove (b, w, h, image);
    /* Матрица умножения */
    int matrix[5][5] = { { -1, -1, -1, -1, -1},
			 { -1, -1, -1, -1, -1},
			 { -1, -1, 25, -1, -1},
			 { -1, -1, -1, -1, -1},
			 { -1, -1, -1, -1, -1}};
    

    /* Для всех слоёв */
    for (int p = 0; p < 3; p++) {
	/* Для всех строк */
	for (i = 0; i < h; i++) {
	    /* Для каждого пикселя */
	    for(j = 0; j < w; j++) {
		double sum = 0;
		/* Умножаем на матрицу окр.элементы */
		for (int sm = -2; sm < 3; sm++) {
		    for (int lm = -2; lm < 3; lm++) {
			int y = i + sm;
			int x = j + lm;
			if (y < 0) y = 0;
		        if (x < 0) x = 0;
			if (y >= (int) h) y = (int) h - 1;
		        if (x >= (int) w) x = (int) w - 1;
			sum = sum + matrix[sm + 2][lm + 2] *
			    b[p * h * w + y * w  + x];
		    }
		}
		if (sum > 1) sum = 1;
		if (sum < 0) sum = 0;
		image.pixel_array[p * h * w + i * w + j] = sum;            
		/*if (image.pixel_array[p * h * w + i * w + j] == 1 ) {
		    printf("%f \n" , image.pixel_array[p * h * w + i * w + j]);
		    }*/
	    }
	}
    }
    free(b);
}

/**
* @brief Вспомогательная функция для создания расширенного изображения
* @param image Изначальное изображение класса bmp_image.
* @param w Ширина изначального изображения.
* @param h Высота изначального изображения.
* @param b  Ссылка на массив для пикселей нового изображения.
*/
void mprove(double *b, unsigned int w, unsigned h, bmp_image image) {
    unsigned int s,l; /* Индексы */ 
    for (s = 0; s < h; s++) {
        for(l = 0; l < w; l++) {
            b [0 * h  * w + s * w  + l]
		=image.pixel_array[0 * h * w + s * w + l];
	    b [1 * h * w + s * w + l]
		=image.pixel_array[1 * h * w + s * w + l];
	    b [2 * h * w + s * w + l]
		=image.pixel_array[2 * h * w + s * w + l];
        }    
    }
}
