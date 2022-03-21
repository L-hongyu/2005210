#include <iostream>
#include <string>
#include <cstdlib>
#include<fstream>
#include<sstream>
#include <algorithm>//reverse����������ӵ�ͷ�ļ�
using namespace std;
ofstream linker("����������.txt", ios::app);

void show()//������Ҫ���ļ��������������չʾ
{

    ifstream output;
    output.open("����������.txt", ios::in);
    char all[1024];
    while (output.getline(all, sizeof(all)))//�������
    {
        cout << all << endl;
    }
    cout << "�ϴ���������ȫ������" << endl;
}
string MUL_INT(string num1, string num2)//�˷������㺯��
{
    int len1 = num1.length(), len2 = num2.length();
    int len = len1 + len2 + 1;
    reverse(num1.begin(), num1.end());
    reverse(num2.begin(), num2.end());
    //tmp����ÿ�γ˷��Ľ����res���������ӵĽ��
    //char res[len], tmp[len];
    char* res = new char[len];
    char* tmp = new char[len];
    for (int i = 0; i < len; i++)
    {
        res[i] = '0';
        tmp[i] = '0';
    }
    for (int i = 0; i < len1; i++)
    {
        //jinwei����ÿ�γ˷��Ľ�λ��r_jw���������ӵĽ�λ
        int jinwei = 0, r_jw = 0;
        for (int j = 0; j < len2; j++)
        {
            tmp[j] = ((num1[i] - '0') * (num2[j] - '0') + jinwei) % 10 + '0';//�������һλ��˽�λ֮��ʣ�µ���

            int res_temp = (res[j + i] - '0') + (tmp[j] - '0') + r_jw;

            res[j + i] = res_temp % 10 + '0'; //�������ս��

            jinwei = ((num1[i] - '0') * (num2[j] - '0') + jinwei) / 10;//��Ľ�λ���Ǽ���jw�͵��ڼ�
            r_jw = res_temp / 10; //r_jw���������ӵĽ�λ
        }
        //������λ�н�λ
        if (r_jw != 0 || jinwei != 0)
        {
            res[len2 + i] = jinwei + r_jw + '0';
        }
    }
    string result = "";
    bool flag = false;
    for (int i = len - 1; i >= 0; i--)
    {
        //������һ�������� 
        if (res[i] != '0' && !flag)
        {
            result += res[i];
            flag = true;
        }
        else if (flag)
            result += res[i];
    }
    if (result == "") result = "0";
    return result;
}
inline int compare(string s1, string s2)//��ȷ���0�����ڷ���1��С�ڷ���-1
{
    if (s1.size() < s2.size())
        return -1;
    else if (s1.size() > s2.size())
        return 1;
    else
        return s1.compare(s2);//��������ȣ���ͷ��β��λ�Ƚ�
}
class App
{
public:
    void Menu();
    void Process();
    int GetStart();
    void Run();
};
class HugeInt
{
public:
    string values;//��������λ�ϵ�����
    bool flag;//true��ʾ������false��ʾ������0Ĭ��Ϊ����

public:
    HugeInt() :values("0"), flag(true) {};
    HugeInt(string str)//����ת�����캯��(Ĭ��Ϊ������)
    {
        values = str;
        flag = true;
    }
public:

    friend ostream& operator << (ostream& os, const HugeInt& hugeInt);//�������������
    friend istream& operator>>(istream& is, HugeInt& bigInt);//�������������
    HugeInt operator+(const HugeInt& rhs);//�ӷ���������
    HugeInt operator-(const HugeInt& rhs);//������������

    HugeInt operator/(const HugeInt& rhs);//������������
    HugeInt operator%(const HugeInt& rhs);//ȡ���������
    HugeInt& operator++(int)//�ԼӲ�������
    {

        HugeInt sho;
        string number;
        cout << "�ԼӶ��ٴ�" << endl;
        cin >> number;
        sho.values = number;
        HugeInt c(this->values);
        c = c + sho;
        cout << "�Լӽ��Ϊ��" << c.values << endl;

        linker << c.values << endl;
        return c;

    }
    HugeInt& operator--(int)//�Լ���������
    {

        HugeInt sho;
        string number;
        cout << "�Լ����ٴ�" << endl;
        cin >> number;
        sho.values = number;
        HugeInt c(this->values);
        c = c - sho;
        cout << "�Լ����Ϊ��" << c.values << endl;

        //linker << c.values << endl;
        return c;
    }
    void transform()
    {

        char str[100];
        strcpy_s(str, values.c_str());//����һ��ָ���ַ�����ָ�볣��
        int num = atoi(str);//��string����ת��Ϊint����
        cout << "ת��Ϊint����Ϊ��" << num << endl;

        linker << num << endl;
    }
};


/*
��������ȡ�����'>>'�����һ������
*/
ostream& operator << (ostream& os, const HugeInt& hugeInt)
{
    if (!hugeInt.flag)
    {
        os << '-';
    }
    os << hugeInt.values;
    return os;
}
/*
���������������'>>'������һ��������
*/
istream& operator >> (istream& is, HugeInt& hugeInt)
{
    string str;
    is >> str;
    hugeInt.values = str;
    hugeInt.flag = true;
    return is;
}

/*
�������������
*/
HugeInt HugeInt::operator+(const HugeInt& rhs)
{
    HugeInt ret;
    ret.flag = true;//��������Ӻ�Ϊ����
    string lvalues(values), rvalues(rhs.values);
    //�����������

    if (lvalues == "0")
    {
        ret.values = rvalues;
        return ret;
    }
    if (rvalues == "0")
    {
        ret.values = lvalues;
        return ret;
    }
    //����s1��s2�ĳ���
    unsigned int i, str1, str2;
    str1 = lvalues.size();
    str2 = rvalues.size();
    if (str1 < str2)
    {
        for (i = 0; i < str2 - str1; i++)//��lvalues��߲���
        {
            lvalues = "0" + lvalues;
        }
    }
    else
    {
        for (i = 0; i < str1 - str2; i++)//��rvalues��߲���
        {
            rvalues = "0" + rvalues;
        }
    }
    //���������
    int n1, n2;
    n2 = 0;
    str1 = lvalues.size();
    string res = " ";
    reverse(lvalues.begin(), lvalues.end());//�ߵ��ַ������Է���ӵ�λ�������
    reverse(rvalues.begin(), rvalues.end());
    for (i = 0; i < str1; i++)
    {
        n1 = (lvalues[i] - '0' + rvalues[i] - '0' + n2) % 10;//n1����ǰλ��ֵ
        n2 = (lvalues[i] - '0' + rvalues[i] - '0' + n2) / 10;//n2�����λ
        res = res + char(n1 + '0');
    }

    if (n2 == 1)
    {
        res = res + "1";
    }
    reverse(res.begin(), res.end());

    ret.values = res;

    linker << ret.values << endl;
    return ret;
}
/*
�������������
*/
HugeInt HugeInt::operator-(const HugeInt& rhs)
{
    HugeInt ret;
    string lvalues(values), rvalues(rhs.values);
    //�����������

    if (rvalues == "0")
    {
        ret.values = lvalues;
        ret.flag = true;
        return ret;
    }
    if (lvalues == "0")
    {
        ret.values = rvalues;
        ret.flag = false;
        return ret;
    }
    //����s1��s2�ĳ���
    unsigned int i, str1, str2;
    str1 = lvalues.size();
    str2 = rvalues.size();
    if (str1 < str2)
    {
        for (i = 0; i < str2 - str1; i++)//��lvalues��߲���
        {
            lvalues = "0" + lvalues;
        }
    }
    else
    {
        for (i = 0; i < str1 - str2; i++)//��rvalues��߲���
        {
            rvalues = "0" + rvalues;
        }
    }
    //����ʹ��-����ǰ�ߵ������ں�ߵ���
    int t = lvalues.compare(rvalues);//��ȷ���0��str1<str2���ظ�����str1>str2��������
    if (t < 0)
    {
        ret.flag = false;
        string t = lvalues;
        lvalues = rvalues;
        rvalues = t;
    }
    else if (t == 0)
    {
        ret.values = "0";
        ret.flag = true;
        return ret;
    }
    else
    {
        ret.flag = true;
    }
    //���������
    unsigned int j;
    str1 = lvalues.size();
    string res = "";
    reverse(lvalues.begin(), lvalues.end());//�ߵ��ַ������Է���ӵ�λ�������
    reverse(rvalues.begin(), rvalues.end());
    for (i = 0; i < str1; i++)
    {
        if (lvalues[i] < rvalues[i])//���㣬��ǰ��һλ
        {
            j = 1;
            while (lvalues[i + j] == '0')
            {
                lvalues[i + j] = '9';
                j++;
            }
            lvalues[i + j] -= 1;
            res = res + char(lvalues[i] + ':' - rvalues[i]);
        }
        else
        {
            res = res + char(lvalues[i] - rvalues[i] + '0');
        }
    }
    reverse(res.begin(), res.end());
    res.erase(0, res.find_first_not_of('0'));//ȥ��ǰ����

    ret.values = res;

    linker << ret.values << endl;
    return ret;
}
/*
�������������
*/
HugeInt operator*(HugeInt& t1, HugeInt& t2)//���س˺������
{
    return MUL_INT(t1.values, t2.values);
}
/*
�������������
*/
HugeInt HugeInt::operator/(const HugeInt& rhs)
{
    HugeInt ret;
    string lvalues(values), rvalues(rhs.values);
    string quotient;
    string temp;
    //�����������
    if (rvalues == "0")
    {
        ret.values = "error";//�������
        ret.flag = true;
        return ret;
    }
    if (lvalues == "0")
    {
        ret.values = "0";
        ret.flag = true;
        return ret;
    }

    if (compare(lvalues, rvalues) < 0)
    {
        ret.values = "0";
        ret.flag = true;
        return ret;
    }
    else if (compare(lvalues, rvalues) == 0)
    {
        ret.values = "1";
        ret.flag = true;
        return ret;
    }
    else
    {
        //���������

        unsigned int lsize, rsize;
        lsize = lvalues.size();
        rsize = rvalues.size();
        int i;
        if (rsize > 1) temp.append(lvalues, 0, rsize - 1);
        for (i = rsize - 1; i < lsize; i++)
        {
            temp = temp + lvalues[i];
            //����
            for (char c = '9'; c >= '0'; c--)
            {
                HugeInt re = (HugeInt)rvalues;
                HugeInt le = (HugeInt)string(1, c);
                HugeInt t = re * le;
                HugeInt s = (HugeInt)temp - t;

                if (s.flag == true)
                {
                    temp = s.values;
                    quotient = quotient + c;
                    break;
                }
            }
        }
    }
    //ȥ��ǰ����
    quotient.erase(0, quotient.find_first_not_of('0'));
    ret.values = quotient;
    ret.flag = true;

    return ret;

}
/*
����������ȡ��
*/
HugeInt HugeInt::operator%(const HugeInt& rhs)
{
    HugeInt ret, kj(values), ki(rhs.values);
    string lvalues(values), rvalues(rhs.values);
    string remainder;
    string temp;
    //�����������
    if (rvalues == "0")
    {
        ret.values = "error";//�������
        ret.flag = true;
        return ret;
    }
    if (lvalues == "0")
    {
        ret.values = "0";
        ret.flag = true;
        return ret;
    }

    if (compare(lvalues, rvalues) < 0)
    {
        if (flag == false)
        {
            ret.values = (ki - kj).values;
            ret.flag = true;
            return ret;
        }
        else {
            ret.values = lvalues;
            ret.flag = true;
            return ret;
        }
    }
    else if (compare(lvalues, rvalues) == 0)
    {
        ret.values = "0";
        ret.flag = true;
        return ret;
    }
    else
    {
        //���������
        unsigned int lsize, rsize;
        lsize = lvalues.size();
        rsize = rvalues.size();
        int i;
        if (rsize > 1) temp.append(lvalues, 0, rsize - 1);
        for (i = rsize - 1; i < lsize; i++)
        {
            if (temp == "0") {
                temp = lvalues[i];
            }
            else {
                temp = temp + lvalues[i];
            }
            //����
            for (char c = '9'; c >= '0'; c--)
            {
                HugeInt re = (HugeInt)rvalues;
                HugeInt le = (HugeInt)string(1, c);
                HugeInt t = re * le;
                HugeInt s = (HugeInt)temp - t;

                if (s.flag == true)
                {
                    //cout<<s.values<<endl;
                    temp = s.values;
                    remainder = remainder + c;
                    break;
                }
            }
        }
    }
    //ȥ��ǰ����
    remainder.erase(0, remainder.find_first_not_of('0'));
    ret.values = temp;
    ret.flag = true;

    return ret;
}

void App::Menu()
{
    cout << "*********************" << "�������������������ʵ��" << "************************" << endl
        << "*********************" << "0.�˳�ϵͳ" << "**************************************" << endl
        << "*********************" << "1.�������ӷ�����" << "********************************" << endl
        << "*********************" << "2.��������������" << "********************************" << endl
        << "*********************" << "3.�������˷�����" << "********************************" << endl
        << "*********************" << "4��������������������" << "***************************" << endl
        << "*********************" << "5�������Լ�����" << "*********************************" << endl
        << "*********************" << "6�������Լ�����" << "*********************************" << endl
        << "*********************" << "7������ת������" << "*********************************" << endl
        << "*********************************************************************" << endl;
}
void App::Process()
{
    HugeInt a, b, result;
    cout << "�����빦����ţ�" << endl;
    cout << endl;
    int s;
    while (cin >> s)
    {
        if (s == 0)
        {
            cout << "finish" << endl;
            break;
        }
        switch (s)
        {
        case 0:
        {
            cout << "��ѡ������˳�����ϵͳ!" << endl;
            break;
        }
        case 1:
        {
            cout << "������������������" << endl;
            cin >> a;
            cin.ignore(100, '\n');
            cin.clear();
            cin >> b;
            cout << "��Ϊ��" << a + b << endl;
            break;
        }
        case 2:
        {
            cout << "������������������" << endl;
            cin >> a;
            cin.ignore(100, '\n');
            cin.clear();
            cin >> b;
            cout << "��Ϊ��" << a - b << endl;
            break;
        }
        case 3:
        {
            cout << "������������������" << endl;
            cin >> a;
            cin.ignore(100, '\n');
            cin.clear();
            cin >> b;
            cout << "��Ϊ��" << a * b << endl;
            linker << (a * b).values << endl;
            break;
        }
        case 4:
        {
            cout << "������������������" << endl;
            cin >> a;
            cin.ignore(100, '\n');
            cin.clear();
            cin >> b;
            cout << "��Ϊ��" << a / b << endl
                << "����Ϊ��" << a % b << endl;
            linker << (a / b).values << endl;
            linker << (a % b).values << endl;
            break;
        }
        case 5:
        {
            cout << "������һ������" << endl;
            cin >> a;
            a++;
            linker << a.values << endl;
            break;
        }
        case 6:
        {
            cout << "������һ������" << endl;
            cin >> a;
            a--;
            linker << a.values << endl;
            break;
        }
        case 7:
        {
            cout << "������һ������" << endl;
            cin >> a;
            a.transform();
            break;
        }
        default:
        {
            cout << "�������!" << endl; break;
        }
        }

    }
    cout << endl;

}
int App::GetStart()
{
    while (true) {
        cout << "���س���������w���˳�ϵͳ!" << endl;
        char ch = getchar();
        if (ch == '\n') {
            system("cls");//����ϵͳ���������������
            return 1;
        }
        else if (ch == 'w' || ch == 'W')
            return 0;
    }
}
void App::Run()
{
    int b;
    do {
        Menu();
        Process();
        b = GetStart();
    } while (b != 0);
}

int main()
{
    char op;
    App c1;
    c1.Run();
    linker.close();
    return 0;
}