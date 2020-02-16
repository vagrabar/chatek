#include <iostream>
#include <imsl.h>
#include <fstream>
#include <math.h>
#include <cmath>

#define F(x) (float) (x*sin(x))//Функция

using namespace std;

int main()
{
        ofstream O ("output.txt");
        O<<"=====\nGrabar Slava\n=====\n3430302/80005\nVariant: 5\n=====\nWelcome to the party!\n\n";
        O<<"This is MY function that I need to interpolate:\nF(x) = x*sin(x)\n\n=====\n";
        O<<"The range of values: [0; PI]\n\n";

    Imsl_d_spline *ppoly, *ppoly1, *ppoly2, *ppoly3, *ppoly4, *ppoly5;
    int NDATA[] = {10, 20, 40, 80};
    double NDATA_f[] = {10, 20, 40, 80};
    double a = 0, b = (double)acos(-1), errdata[4] = {}, h[4] = {}, Diff[] = {}, I = 0, S = 0;
    double errdata1[4] = {}, errdata2[4] = {}, errdata3[4] = {}, errdata4[4] = {}, errdata5[4] = {};
    double Int_F1, Int_F2, Int_F3;
    double xdata[80+1] = {}, fdata[80+1] = {}, x, y, f, epsilon, epsilon1, epsilon2, epsilon3, epsilon4, epsilon5;
    double f1data[80+1] = {}, f2data[80+1] = {}, f3data[80+1] = {};
    double y1 = 0, y2 = 0, y3 = 0, y4 = 0, y5 = 0;
    double Pogr_for_1[4] = {}, Pogr_for_2[4] = {}, Pogr_for_3[4] = {}, Pogr_for_4[4] = {}, Pogr_for_5[4] = {}, Pogr[4] = {};

    for(int i = 0; i < 4; i++)
    {
        errdata[i] = 0;
        h[i] = (b - a)/(8 * NDATA_f[i]);
        x = a;
        O << "N is: " << NDATA[i] << endl;
        for(int j = 0; j < NDATA[i] + 1; j++)//Формирование точек графика по числу разбиений
        {
            xdata[j] = a + j * ((b - a)/NDATA_f[i]);
            fdata[j] = F(xdata[j]);

        }
        ppoly = imsl_d_spline_interp(NDATA[i] + 1, xdata, fdata, 0);//Построение полинома B-сплайна функции
        //В первой функции автоматически берётся четвёртая степень => берёт по умолчанию k-1 значение
        ppoly2 = imsl_d_spline_interp(NDATA[i] + 1, xdata, fdata, IMSL_ORDER, 2, 0);//Построение полинома B-сплайна функции 2 order
        ppoly3 = imsl_d_spline_interp(NDATA[i] + 1, xdata, fdata, IMSL_ORDER, 3, 0);//Построение полинома B-сплайна функции 3 order
        ppoly4 = imsl_d_spline_interp(NDATA[i] + 1, xdata, fdata, IMSL_ORDER, 4, 0);//Построение полинома B-сплайна функции 4 order
        ppoly5 = imsl_d_spline_interp(NDATA[i] + 1, xdata, fdata, IMSL_ORDER, 5, 0);//Построение полинома B-сплайна функции 5 order

        O<<"X\t\tY\t\tInterpolant\tErrory\t\tError for 2\tError for 3\tError for 4\tError for 5\n";
        double Integ_S = 0, Integ_S1 = 0, Integ_S2 = 0, Integ_S3 = 0, Int_F = 0, errory = 0;
        for(int j = 0; j < 8 * NDATA[i] + 1; j++)//Составление аппроксимации
        {
            y = imsl_d_spline_value(x, ppoly, 0);//Подсчёт точек У графика функции
            y2 = imsl_d_spline_value(x, ppoly2, 0);//Подсчёт точек У В-сплайна 2 степени
            y3 = imsl_d_spline_value(x, ppoly3, 0);//Подсчёт точек У В-сплайна 3 степени
            y4 = imsl_d_spline_value(x, ppoly4, 0);//Подсчёт точек У В-сплайна 4 степени
            y5 = imsl_d_spline_value(x, ppoly5, 0);//Подсчёт точек У В-сплайна 5 степени
            f = F(x);

            //Разница между сплайнами и функцией
            errory = abs(f - y);//0шибка функции и сплайна без степени
            epsilon2 = abs(f - y2);//Ошибка функции и В-сплайна 1 степени
            epsilon3 = abs(f - y3);//Ошибка функции и В-сплайна 1 степени
            epsilon4 = abs(f - y4);//Ошибка функции и В-сплайна 1 степени
            epsilon5 = abs(f - y5);//Ошибка функции и В-сплайна 1 степени

            //Вывод в файл полученных значений
            O<<fixed<<x<<"\t"<<scientific<<f<<"\t"<<scientific<<y<<"\t"<<scientific<<errory<<"\t"<<scientific<<epsilon2<<"\t"<<scientific<<epsilon3<<"\t"<<scientific<<epsilon4<<"\t"<<scientific<<epsilon5<<endl;
            //Поиск максимального отклонения полинома от функции
            if(errory > errdata[i]){errdata[i] = errory;}
            if(epsilon2 > errdata2[i]){errdata2[i] = epsilon2;}
            if(epsilon3 > errdata3[i]){errdata3[i] = epsilon3;}
            if(epsilon4 > errdata4[i]){errdata4[i] = epsilon4;}
            if(epsilon5 > errdata5[i]){errdata5[i] = epsilon5;}

            x += h[i];
        }

        O<<"Errory is: "<<fixed<<errdata[i]<<endl;//Ошибка сплайна(функции)
        O<<"Error for 2 is: "<<fixed<<errdata2[i]<<endl;//Ошибка В-сплайна 2 степени
        O<<"Error for 3 is: "<<fixed<<errdata3[i]<<endl;//Ошибка В-сплайна 3 степени
        O<<"Error for 4 is: "<<fixed<<errdata4[i]<<endl;//Ошибка В-сплайна 4 степени
        O<<"Error for 5 is: "<<fixed<<errdata5[i]<<endl;//Ошибка В-сплайна 5 степени

        Pogr[i] = errdata[i];
        Pogr_for_2[i] = errdata2[i];
        Pogr_for_3[i] = errdata3[i];
        Pogr_for_4[i] = errdata4[i];
        Pogr_for_5[i] = errdata5[i];
        cout<<Pogr[i]<<"\t"<<Pogr_for_2[i]<<"\t"<<Pogr_for_3[i]<<"\t"<<Pogr_for_4[i]<<"\t"<<Pogr_for_5[i]<<endl;

        O<<"\n=====\n";
    }

    for(int i = 0; i < 3; i++)
    {
        O << "\nError between err["<< i+1 <<"] and err["<< i+2 <<"] = "<<Pogr[i]/Pogr[i+1]<<endl;
        O << "\nError between err for 2["<< i+1 <<"] and err for 2["<< i+2 <<"] = "<<Pogr_for_2[i]/Pogr_for_2[i+1]<<endl;
        O << "\nError between err for 3["<< i+1 <<"] and err for 3["<< i+2 <<"] = "<<Pogr_for_3[i]/Pogr_for_3[i+1]<<endl;
        O << "\nError between err for 4["<< i+1 <<"] and err for 4["<< i+2 <<"] = "<<Pogr_for_4[i]/Pogr_for_4[i+1]<<endl;
        O << "\nError between err for 5["<< i+1 <<"] and err for 5["<< i+2 <<"] = "<<Pogr_for_5[i]/Pogr_for_5[i+1]<<endl;
        O << "=====\n";
    }

    O<<endl;
        return 0;
}
