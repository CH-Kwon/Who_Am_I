/**
 \file
 \author
 \par         email:
 \par         course: GAM200
 \date        ?/?/2017
 \brief
 
 */

#pragma once
namespace FindersEngine
{
	int Secretnumber[4];
	int GetSecretnumber[4];


	void GetSecretNumber(int number, int index)
	{
		GetSecretnumber[index] = number;
	}

	bool SecretNumberChecking()
	{
		for (int i = 0; i < 4; i++)
		{
			if (Secretnumber[i] != GetSecretnumber[i])
			{
				return false;
			}
		}
		return true;
	}

}