#pragma once
double range(double n, double min, double max);
double range(double n);
//���͂��ꂽ�ϐ�n���Amin��max�Ŏw�肳�ꂽ�͈͂ɐ������܂��B
//�͈͊O�̐��l�����͂��ꂽ�ꍇ�́A��O�𑗏o���܂��B
double clamp(double n, double min, double max);
//���͂��ꂽ�ϐ�n���A0�`1�͈̔͂ɐ������܂��B
//�͈͊O�̐��l�����͂��ꂽ�ꍇ�́A��O�𑗏o���܂��B
double clamp(double n);
//���͂��ꂽ�ϐ�n���Amin��max�Ŏw�肳�ꂽ�͈͂ɐ������܂��B
//�͈͊O�̐��l�����͂��ꂽ�ꍇ�́Amin��������max��Ԃ��܂��B
double clamp_s(double n, double min, double max);
//���͂��ꂽ�ϐ�n���A0�`1�͈̔͂ɐ������܂��B
//�͈͊O�̐��l�����͂��ꂽ�ꍇ�́A0��1��Ԃ��܂��B
double clamp_s(double n);