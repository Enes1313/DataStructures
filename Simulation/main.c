/********************************************************************************
* DESCRIPTION : It is simulation program.
* NOTES       : None
* STANDARD    : C90 and up
* Author      : Enes AYDIN
********************************************************************************/

/********************************************************************************
 ****** Simulasyon Problemi
 *
 * M (150) metre uzunluğunda, kutuları H (1) m/sn hızla çıkış noktalarına götüren
 * konveyör kurulmak istenmektedir. Bu konveyör'ün kapasitesi ortalama K (1500)
 * kutu/saat olacaktır. (Ortalama 60 * 60 / Y (2.4) sn'de bir kutu girecektir.)
 *
 * Konveyör'ün Y (18) tane birbirine eşit uzaklıkta olan yerlerinde C (1|2) tane
 * çıkış olacaktır. Konveyor'ün amacı kutuları Y * C (18|36) tane ayrı çıkışa
 * dağıtmaktır. Her bir kutu konveyör'e girdiğinde hangi çıkışa gideceği A (rand)
 * sistemi ile bilinmektedir.
 *
 * Her çıkışda bulunan P (3) personelden biri sadece bir kutuyu alır ve belirli
 * işlemleri gerçekleştirir. (Bu işlemlerde "kutuyu alma, hedefine götürme ve geri
 * gelme" eylemleri bulunmaktadır). İşlemdeyken bir personel ortalama T (25) saniye
 * sonra boş olur ve ancak o zaman yeni bir kutuyla işlem yapacak duruma gelir.
 *
 * Sistemi G (7) gün simüle eden S (1) saatte bir logları yazdıran programı yazınız.
 *
 ****** İstenen Loglar
 *
 * O anki konveyor hatta bulunan kutu sayısı,
 * O ana kadar konveyor'e gelen toplam kutu sayısı,
 * P * C tane çıkıştaki personellerin daha ilgilenmeye başlamadığı kutu sayısı.
 *
 ****** Not
 *
 * Sistemin görselliği istenmemektedir. Konsol uygulaması yeterlidir.
 * (JS kullacaksanız başka :D)
 *
 * M, H, K, Y, C, P, T, G ve S değerleri değişmez değişkenlerdir. (C için const
 * veya #define ile tanımlayabilirsiniz.) Bu değişkenlerin örnek değerleri problem ,
 * anlatırken parantez içince verilmiştir.
 *
 * C değeri için iki örnek değer verilmiştir. '2' değerini kullanın.
 *
 * A sistemi için simülasyonda rastgele sayı üreteçleri kullanın. (C için rand
 * fonksiyonu)
 *
 * Lif (thread) kullanmadan yapmaya çalışın. (Kullanabilirsiniz de)
 *
 * Ek kütüphane veya hazır fonksiyonlar kullanabilirsiniz. (Veri yapıları vb.)
 *
 * Konveyör'ün ilk çıkışları direk girişinde değildir. (Konveyör uzunluğundan ve
 * eşit uzaklıkta olan Y yerin mesafelerini bulurken ilk yerin konveyör'ün başında
 * olmadığını kabul edin.)
 *
 * Çıkış denilen yer de bir konveyör, kutular sırayla gelir ve personeller sırayla
 * buradaki kutuları alır. Buradaki sürenin veya konveyör'ün çalışmasının önemsiz
 * kabul edilerek parametrelendirilmemiştir veya gerekli değerleri değiştirerek
 * (örneğin 25 sn'yi 28 sn yaparak) buradaki sistem az-çok modellenebilmektedir.
 *
 * Simülasyon gerçek zamanla çalışmasına gerek yoktur. Yoksa 7 gün bir simülasyon
 * sürer :D
 *******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "eaDSDynamicArray.h"

#define HOURLY_LOG										1		/* hours */
#define SIMULATION_DAYS									7		/* days */
#define COUNT_LOCATIONS 								36
#define COUNT_LOCATIONS_SAME_LINE 						2		/* 1 or 2 */
#define WORKERS_PER_SAME_LOCATIONS						3		/* >= 2 */
#define LENGTH_OF_CONVEYOR								150		/* meters */
#define HOURLY_PERFORMENCE 								1500	/* boxes entry per hour */
#define WAITING_BOX_TO_FINISH 							25000	/* ms */
#define SPEED_OF_BOX_ON_CONVEYOR						1		/* m/sn */

typedef struct _Box {
	int id;
	int way;
	int location;
	int waitingOnLocation;
} Box;

const int LOG_TIME = HOURLY_LOG * 60 * 60 * 1000;
const int NEW_BOX = 60 * 60 * 1000 / HOURLY_PERFORMENCE;
const int TOTAL_SIMULATION_TIME = SIMULATION_DAYS * 24 * 60 * 60 * 1000;
const int DISTANCE_BETWEEN_TWO_LOCATIONS_IN_DIFFERENT_LINE = LENGTH_OF_CONVEYOR / (COUNT_LOCATIONS / COUNT_LOCATIONS_SAME_LINE);

void freeMemory(eaDSDynamicArray dynamicArray1, eaDSDynamicArray * dynamicArray2);
void debugFreeExit(const char * msg, eaDSDynamicArray dynamicArray1, eaDSDynamicArray * dynamicArray2);

void * boxCreateAndCopy(const void * data)
{
	void * a = malloc(sizeof(Box));
	return memcpy(a, data, sizeof(Box));
}

int boxCompare(const void * p1, const void * p2)
{
	if (((Box *)p1)->id == ((Box *)p2)->id)
	{
		return 0;
	}
	return (((Box *)p1)->id > ((Box *)p2)->id) * 2 - 1;
}

void boxClear(void * a)
{
	free(a);
}

int main()
{
	size_t i, j, control_mem = 1;
	eaDSDynamicArray dynamicArray1;
	eaDSDynamicArray dynamicArray2[COUNT_LOCATIONS];

	if (NULL == (dynamicArray1 = eaDSDynamicArrayInit(boxCreateAndCopy, boxCompare, boxClear)))
	{
		control_mem = 0;
	}

	for (i = 0; i < COUNT_LOCATIONS; i++)
	{
		if (NULL == (dynamicArray2[i] = eaDSDynamicArrayInit(boxCreateAndCopy, boxCompare, boxClear)))
		{
			control_mem = 0;
			break;
		}
	}

	if (control_mem)
	{
		Box box, * pBox;
		int counter = 0;
		int product_uniqe_id = 0;
		int interval = SPEED_OF_BOX_ON_CONVEYOR * 1000;

		srand((unsigned int)time(NULL));

		for (i = 2;;)
		{
			if ((NEW_BOX % interval == 0) && (LOG_TIME % interval == 0) && (WAITING_BOX_TO_FINISH % interval == 0))
			{
				break;
			}

			while((SPEED_OF_BOX_ON_CONVEYOR * 1000) % i) i++;
			interval = (SPEED_OF_BOX_ON_CONVEYOR * 1000) / (int)i++;
		}

		printf("Hourly log\t\t\t\t\t: %6.1f hour!\n", (float) HOURLY_LOG);
		printf("Simulation days\t\t\t\t\t: %6d days!\n", SIMULATION_DAYS);
		printf("Count locations\t\t\t\t\t: %6d targets!\n", COUNT_LOCATIONS);
		printf("Count locations on same line\t\t\t: %6d targets!\n", COUNT_LOCATIONS_SAME_LINE);
		printf("Workers per same locations\t\t\t: %6d workers!\n", WORKERS_PER_SAME_LOCATIONS);
		printf("Length of conveyor\t\t\t\t: %6d meters!\n", LENGTH_OF_CONVEYOR);
		printf("Hourly performence\t\t\t\t: %6d boxes/hour!\n", HOURLY_PERFORMENCE);
		printf("Last waiting box to finish on location\t\t: %6d ms!\n", WAITING_BOX_TO_FINISH);
		printf("Speed of box on conveyor\t\t\t: %6d meter!\n\n", SPEED_OF_BOX_ON_CONVEYOR);

		printf("New box\t\t\t\t\t\t: %6d per ms!\n", NEW_BOX);
		printf("Distance between two locations\t\t\t: %6d m!\n", DISTANCE_BETWEEN_TWO_LOCATIONS_IN_DIFFERENT_LINE);
		printf("Interval value\t\t\t\t\t: %6d ms!\n\n", interval);

		printf("Press enter to start!\n\n\n");
		getchar();

		for (counter = 0; counter <= TOTAL_SIMULATION_TIME; counter += interval)
		{
			/* logging */
			if (counter % LOG_TIME == 0)
			{
				printf("Passed time\t\t: %15d hour!\n", counter / 1000 / 3600);
				printf("All boxes\t\t: %15d boxes!\n", product_uniqe_id);
				printf("Total boxes in conveyor\t: %15d boxes!\n", (int) eaDSDynamicArrayGetCount(dynamicArray1));
				printf("Total boxes on locations\t:\n");

				for (i = 0; i < COUNT_LOCATIONS; ++i) {
					printf("%4d ", (int) eaDSDynamicArrayGetCount(dynamicArray2[i]));
				}
				printf("boxes!\n\n");
			}

			/* new box */
			if (counter % NEW_BOX == 0)
			{
				box.id = product_uniqe_id++;
				box.location = rand() % COUNT_LOCATIONS + 1;
				box.waitingOnLocation = WAITING_BOX_TO_FINISH;
				box.way = ((box.location + COUNT_LOCATIONS_SAME_LINE - 1) / COUNT_LOCATIONS_SAME_LINE) * DISTANCE_BETWEEN_TWO_LOCATIONS_IN_DIFFERENT_LINE * 1000; /* mm */

				if (EXIT_FAILURE == eaDSDynamicArrayAdd(dynamicArray1, &box))
				{
					debugFreeExit("Dinamik dizi'ye eleman eklenemedi!", dynamicArray1, dynamicArray2);
				}
			}

			/* moving */
			for(i = 0; NULL != (pBox = (Box *) eaDSDynamicArrayGetAddressFrom(dynamicArray1, i)); i++)
			{
				if ((pBox->way -= SPEED_OF_BOX_ON_CONVEYOR * interval) <= 0) /* ... / 1000 * 1000  = ... / 1 */
				{
					if(EXIT_SUCCESS == eaDSDynamicArrayAdd(dynamicArray2[pBox->location - 1], pBox))
					{
						eaDSDynamicArrayRemoveAtCopyLastItem(dynamicArray1, i--);
					}
					else
					{
						debugFreeExit("Dinamik dizi'ye eleman eklenemedi!", dynamicArray1, dynamicArray2);
					}
				}
			}

			/* controlling */
			for (i = 0; i < COUNT_LOCATIONS; i++)
			{
				for(j = 0; (NULL != (pBox = (Box *) eaDSDynamicArrayGetAddressFrom(dynamicArray2[i], j))) && (j < WORKERS_PER_SAME_LOCATIONS); j++)
				{
					if ((pBox->waitingOnLocation -= interval) <= 0)
					{
						eaDSDynamicArrayRemoveAtCopyLastItem(dynamicArray2[i], j--);
					}
				}
			}
		}
	}

	/* free memory */
	freeMemory(dynamicArray1, dynamicArray2);

	/* wait for enter to be pressed */
	getchar();

	return EXIT_SUCCESS;
}

void freeMemory(eaDSDynamicArray dynamicArray1, eaDSDynamicArray * dynamicArray2)
{
	int i;

	eaDSDynamicArrayClear(dynamicArray1);

	for (i = 0; i < COUNT_LOCATIONS; i++)
	{
		eaDSDynamicArrayClear(dynamicArray2[i]);
	}
}

void debugFreeExit(const char * msg, eaDSDynamicArray dynamicArray1, eaDSDynamicArray * dynamicArray2)
{
	puts(msg);
	freeMemory(dynamicArray1, dynamicArray2);
	exit(EXIT_FAILURE);
}

