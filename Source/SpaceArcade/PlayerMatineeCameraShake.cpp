/*
*  Библеотеки
*/

#include "PlayerMatineeCameraShake.h"

/*
*  Код
*/

// Иницилизация объекта
UPlayerMatineeCameraShake::UPlayerMatineeCameraShake()
{
	// Продолжительность колебаний
	OscillationDuration = 0.25f;
	// Продолжительность смешивание колебаний в начале
	OscillationBlendInTime = 0.05f;
	// Продолжительность смешивание колебаний в конце
	OscillationBlendOutTime = 0.05f;

	// Рандомной значение амплитуды и частоты по X
	RotOscillation.Pitch.Amplitude = FMath::RandRange(3.0f, 5.0f);
	RotOscillation.Pitch.Frequency = FMath::RandRange(15.0f, 20.5f);

	// Рандомной значение амплитуды и частоты по Y
	RotOscillation.Yaw.Amplitude = FMath::RandRange(3.0f, 5.0f);
	RotOscillation.Yaw.Frequency = FMath::RandRange(15.0f, 20.5f);
}