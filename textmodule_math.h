#pragma once
double range(double n, double min, double max);
double range(double n);
//入力された変数nを、minとmaxで指定された範囲に制限します。
//範囲外の数値が入力された場合は、例外を送出します。
double clamp(double n, double min, double max);
//入力された変数nを、0～1の範囲に制限します。
//範囲外の数値が入力された場合は、例外を送出します。
double clamp(double n);
//入力された変数nを、minとmaxで指定された範囲に制限します。
//範囲外の数値が入力された場合は、minもしくはmaxを返します。
double clamp_s(double n, double min, double max);
//入力された変数nを、0～1の範囲に制限します。
//範囲外の数値が入力された場合は、0か1を返します。
double clamp_s(double n);