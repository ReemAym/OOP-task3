/*
Name: Mariam Ashraf Amin          ID:20200520
Name: Reem Ayman Abd El-fattah    ID:20200186
*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

//FloatArray class
class FloatArray
        {
protected:
            int arr_Size;
            float *Array;
public:
            //Parameterized Constructor
            FloatArray (int size)
            {
                arr_Size=size;
                Array=new float [arr_Size];
            }

            //add Function for FloatArray class
            virtual void add(float element,int index)
            {
                Array[index]=element;
            }

            //Operator overloading >> to read the array elements from the file
            friend ifstream & operator >> (ifstream & Read,FloatArray *Obj);

            //Operator overloading << to write the array to a file
            friend ofstream & operator << (ofstream & Write,FloatArray * Obj);

            //Destructor
            ~ FloatArray()
            {
                delete [] Array;
            }

        };

//SortedArray class
class SortedArray : public FloatArray
        {
        public:
            //Parameterized Constructor
            SortedArray (int size):FloatArray(size)
            {
            }

            //add Function for SortedArray class
            void add(float element,int index)
            {
                if (index==0)
                {
                    Array[index]=element;
                }
                else
                {
                    if (element>=Array[index-1])
                    {
                        Array[index]=element;
                    }
                    else
                    {
                        for (int j = 0; j <index; j++)
                        {
                            if (element<Array[j])
                            {
                                for (int k = index; k >j ; --k)
                                {
                                    Array[k]=Array[k-1];
                                }
                                Array[j]=element;
                                break;
                            }
                        }
                    }
                }
            }
        };

//FrontArray class
class FrontArray : public FloatArray
        {
public:
            //Parameterized Constructor
            FrontArray (int size):FloatArray(size)
            {
            }

            //add Function for FrontArray class
            void add(float element,int index)
            {
                Array[arr_Size-index-1]=element;
            }
        };


//PositiveArray class
class PositiveArray : public SortedArray
        {
        protected:
            int counter =0;
        public:
            //Parameterized Constructor
            PositiveArray (int size):SortedArray(size)
            {
            }

            //add Function for PositiveArray class
            void add(float element,int index)
            {
                if (element>0)
                {
                    SortedArray::add(element,counter);
                    counter++;
                }
                if (index==arr_Size-1)
                {
                    arr_Size=counter;
                }
            }
        };

//NegativeArray class
class NegativeArray : public SortedArray
        {
        protected:
            int counter =0;
        public:
            //Parameterized Constructor
            NegativeArray (int size):SortedArray(size)
            {
            }

            //add Function for NegativeArray class
            void add(float element,int index)
            {
                if (element<0)
                {
                    SortedArray::add(element,counter);
                    counter++;
                }
                if (index==arr_Size-1)
                {
                    arr_Size=counter;
                }
            }
        };

//Operator overloading >> to read the array elements from the file
ifstream & operator >> (ifstream & Read,FloatArray *Obj)
{
    float element;
    for (int i = 0; i < Obj->arr_Size; i++)
    {
        Read>>element;
        Obj->add(element,i);
    }
    return Read;
}


//Operator overloading << to write the array to a file
ofstream & operator << (ofstream & Write,FloatArray * Obj)
{
    Write<< Obj->arr_Size<<"|\t";
    for (int i = 0; i < Obj->arr_Size; i++)
    {
        if (i==(Obj->arr_Size-1))
            Write<<Obj->Array[i];
        else
            Write<<Obj->Array[i]<<"\t";
    }

    return Write;
}

int main()
{
    string input_txt_file, output_txt_file, TypeOfArray;
    int Size;
    FloatArray *array_float[10];

    cout<<"Enter the name of the input file \n";
    cin>>input_txt_file;
    cout<<"Enter the name of the output file \n";
    cin>>output_txt_file;

    ifstream InFile(input_txt_file.c_str());
    ofstream OutFile(output_txt_file.c_str());

    if (InFile)
    {
        for (int i = 0; i < 10; i++)
        {
            InFile>>TypeOfArray;
            InFile>>Size;
            if (TypeOfArray=="Array")
            {
                array_float[i]=new FloatArray(Size);
                InFile>>array_float[i];
                OutFile<<array_float[i];
            }
            else if (TypeOfArray=="Front")
            {
                array_float[i]=new FrontArray(Size);
                InFile>>array_float[i];
                OutFile<<array_float[i];
            }
            else if (TypeOfArray=="Sorted")
            {
                array_float[i]=new SortedArray(Size);
                InFile>>array_float[i];
                OutFile<<array_float[i];
            }
            else if (TypeOfArray=="Positive")
            {
                array_float[i]=new PositiveArray(Size);
                InFile>>array_float[i];
                OutFile<<array_float[i];
            }
            else if (TypeOfArray=="Negative")
            {
                array_float[i]=new NegativeArray(Size);
                InFile>>array_float[i];
                OutFile<<array_float[i];
            }
            OutFile<<endl;

            delete array_float[i];
        }
    }

    InFile.close();
    OutFile.close();


    return 0;
}
