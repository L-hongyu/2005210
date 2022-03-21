#include <iostream>
#include <string>
#include <cstdlib>
#include<fstream>
#include<sstream>
#include <algorithm>//reverse函数所需添加的头文件
using namespace std;
ofstream linker("长整数运算.txt", ios::app);

void show()//根据需要将文件中所有数据输出展示
{

    ifstream output;
    output.open("长整数运算.txt", ios::in);
    char all[1024];
    while (output.getline(all, sizeof(all)))//按行输出
    {
        cout << all << endl;
    }
    cout << "上次输出结果已全部显现" << endl;
}
string MUL_INT(string num1, string num2)//乘法的运算函数
{
    int len1 = num1.length(), len2 = num2.length();
    int len = len1 + len2 + 1;
    reverse(num1.begin(), num1.end());
    reverse(num2.begin(), num2.end());
    //tmp储存每次乘法的结果，res储存最后相加的结果
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
        //jinwei储存每次乘法的进位，r_jw储存最后相加的进位
        int jinwei = 0, r_jw = 0;
        for (int j = 0; j < len2; j++)
        {
            tmp[j] = ((num1[i] - '0') * (num2[j] - '0') + jinwei) % 10 + '0';//求的是这一位相乘进位之后剩下的数

            int res_temp = (res[j + i] - '0') + (tmp[j] - '0') + r_jw;

            res[j + i] = res_temp % 10 + '0'; //储存最终结果

            jinwei = ((num1[i] - '0') * (num2[j] - '0') + jinwei) / 10;//求的进位数是几，jw就等于几
            r_jw = res_temp / 10; //r_jw储存最后相加的进位
        }
        //如果最高位有进位
        if (r_jw != 0 || jinwei != 0)
        {
            res[len2 + i] = jinwei + r_jw + '0';
        }
    }
    string result = "";
    bool flag = false;
    for (int i = len - 1; i >= 0; i--)
    {
        //遇到第一个正整数 
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
inline int compare(string s1, string s2)//相等返回0，大于返回1，小于返回-1
{
    if (s1.size() < s2.size())
        return -1;
    else if (s1.size() > s2.size())
        return 1;
    else
        return s1.compare(s2);//若长度相等，则头到尾按位比较
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
    string values;//保存所有位上的数字
    bool flag;//true表示正数，false表示负数，0默认为正数

public:
    HugeInt() :values("0"), flag(true) {};
    HugeInt(string str)//类型转换构造函数(默认为正整数)
    {
        values = str;
        flag = true;
    }
public:

    friend ostream& operator << (ostream& os, const HugeInt& hugeInt);//重载输出操作符
    friend istream& operator>>(istream& is, HugeInt& bigInt);//输入操作符重载
    HugeInt operator+(const HugeInt& rhs);//加法操作重载
    HugeInt operator-(const HugeInt& rhs);//减法操作重载

    HugeInt operator/(const HugeInt& rhs);//除法操作重载
    HugeInt operator%(const HugeInt& rhs);//取余操作重载
    HugeInt& operator++(int)//自加操作重载
    {

        HugeInt sho;
        string number;
        cout << "自加多少次" << endl;
        cin >> number;
        sho.values = number;
        HugeInt c(this->values);
        c = c + sho;
        cout << "自加结果为：" << c.values << endl;

        linker << c.values << endl;
        return c;

    }
    HugeInt& operator--(int)//自减操作重载
    {

        HugeInt sho;
        string number;
        cout << "自减多少次" << endl;
        cin >> number;
        sho.values = number;
        HugeInt c(this->values);
        c = c - sho;
        cout << "自减结果为：" << c.values << endl;

        //linker << c.values << endl;
        return c;
    }
    void transform()
    {

        char str[100];
        strcpy_s(str, values.c_str());//返回一个指向字符串的指针常量
        int num = atoi(str);//把string类型转化为int类型
        cout << "转换为int类型为：" << num << endl;

        linker << num << endl;
    }
};


/*
重载流提取运算符'>>'，输出一个整数
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
重载流插入运算符'>>'，输入一个正整数
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
两个长整数相加
*/
HugeInt HugeInt::operator+(const HugeInt& rhs)
{
    HugeInt ret;
    ret.flag = true;//正整数相加恒为正数
    string lvalues(values), rvalues(rhs.values);
    //处理特殊情况

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
    //调整s1与s2的长度
    unsigned int i, str1, str2;
    str1 = lvalues.size();
    str2 = rvalues.size();
    if (str1 < str2)
    {
        for (i = 0; i < str2 - str1; i++)//在lvalues左边补零
        {
            lvalues = "0" + lvalues;
        }
    }
    else
    {
        for (i = 0; i < str1 - str2; i++)//在rvalues左边补零
        {
            rvalues = "0" + rvalues;
        }
    }
    //处理本质情况
    int n1, n2;
    n2 = 0;
    str1 = lvalues.size();
    string res = " ";
    reverse(lvalues.begin(), lvalues.end());//颠倒字符串，以方便从低位算起计算
    reverse(rvalues.begin(), rvalues.end());
    for (i = 0; i < str1; i++)
    {
        n1 = (lvalues[i] - '0' + rvalues[i] - '0' + n2) % 10;//n1代表当前位的值
        n2 = (lvalues[i] - '0' + rvalues[i] - '0' + n2) / 10;//n2代表进位
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
两个长整数相减
*/
HugeInt HugeInt::operator-(const HugeInt& rhs)
{
    HugeInt ret;
    string lvalues(values), rvalues(rhs.values);
    //处理特殊情况

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
    //调整s1与s2的长度
    unsigned int i, str1, str2;
    str1 = lvalues.size();
    str2 = rvalues.size();
    if (str1 < str2)
    {
        for (i = 0; i < str2 - str1; i++)//在lvalues左边补零
        {
            lvalues = "0" + lvalues;
        }
    }
    else
    {
        for (i = 0; i < str1 - str2; i++)//在rvalues左边补零
        {
            rvalues = "0" + rvalues;
        }
    }
    //调整使‘-’号前边的数大于后边的数
    int t = lvalues.compare(rvalues);//相等返回0，str1<str2返回负数，str1>str2返回正数
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
    //处理本质情况
    unsigned int j;
    str1 = lvalues.size();
    string res = "";
    reverse(lvalues.begin(), lvalues.end());//颠倒字符串，以方便从低位算起计算
    reverse(rvalues.begin(), rvalues.end());
    for (i = 0; i < str1; i++)
    {
        if (lvalues[i] < rvalues[i])//不足，向前借一位
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
    res.erase(0, res.find_first_not_of('0'));//去掉前导零

    ret.values = res;

    linker << ret.values << endl;
    return ret;
}
/*
两个长整数相乘
*/
HugeInt operator*(HugeInt& t1, HugeInt& t2)//重载乘号运算符
{
    return MUL_INT(t1.values, t2.values);
}
/*
两个长整数相除
*/
HugeInt HugeInt::operator/(const HugeInt& rhs)
{
    HugeInt ret;
    string lvalues(values), rvalues(rhs.values);
    string quotient;
    string temp;
    //处理特殊情况
    if (rvalues == "0")
    {
        ret.values = "error";//输出错误
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
        //处理本质情况

        unsigned int lsize, rsize;
        lsize = lvalues.size();
        rsize = rvalues.size();
        int i;
        if (rsize > 1) temp.append(lvalues, 0, rsize - 1);
        for (i = rsize - 1; i < lsize; i++)
        {
            temp = temp + lvalues[i];
            //试商
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
    //去除前导零
    quotient.erase(0, quotient.find_first_not_of('0'));
    ret.values = quotient;
    ret.flag = true;

    return ret;

}
/*
两个正整数取余
*/
HugeInt HugeInt::operator%(const HugeInt& rhs)
{
    HugeInt ret, kj(values), ki(rhs.values);
    string lvalues(values), rvalues(rhs.values);
    string remainder;
    string temp;
    //处理特殊情况
    if (rvalues == "0")
    {
        ret.values = "error";//输出错误
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
        //处理本质情况
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
            //试商
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
    //去除前导零
    remainder.erase(0, remainder.find_first_not_of('0'));
    ret.values = temp;
    ret.flag = true;

    return ret;
}

void App::Menu()
{
    cout << "*********************" << "长整数计算器的设计与实现" << "************************" << endl
        << "*********************" << "0.退出系统" << "**************************************" << endl
        << "*********************" << "1.长整数加法运算" << "********************************" << endl
        << "*********************" << "2.长整数减法运算" << "********************************" << endl
        << "*********************" << "3.长整数乘法运算" << "********************************" << endl
        << "*********************" << "4长整数除法和求余运算" << "***************************" << endl
        << "*********************" << "5长整数自加运算" << "*********************************" << endl
        << "*********************" << "6长整数自减运算" << "*********************************" << endl
        << "*********************" << "7长整数转换类型" << "*********************************" << endl
        << "*********************************************************************" << endl;
}
void App::Process()
{
    HugeInt a, b, result;
    cout << "请输入功能序号：" << endl;
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
            cout << "您选择的是退出整个系统!" << endl;
            break;
        }
        case 1:
        {
            cout << "请输入两个长整数：" << endl;
            cin >> a;
            cin.ignore(100, '\n');
            cin.clear();
            cin >> b;
            cout << "和为：" << a + b << endl;
            break;
        }
        case 2:
        {
            cout << "请输入两个长整数：" << endl;
            cin >> a;
            cin.ignore(100, '\n');
            cin.clear();
            cin >> b;
            cout << "差为：" << a - b << endl;
            break;
        }
        case 3:
        {
            cout << "请输入两个长整数：" << endl;
            cin >> a;
            cin.ignore(100, '\n');
            cin.clear();
            cin >> b;
            cout << "积为：" << a * b << endl;
            linker << (a * b).values << endl;
            break;
        }
        case 4:
        {
            cout << "请输入两个长整数：" << endl;
            cin >> a;
            cin.ignore(100, '\n');
            cin.clear();
            cin >> b;
            cout << "商为：" << a / b << endl
                << "余数为：" << a % b << endl;
            linker << (a / b).values << endl;
            linker << (a % b).values << endl;
            break;
        }
        case 5:
        {
            cout << "请输入一个数：" << endl;
            cin >> a;
            a++;
            linker << a.values << endl;
            break;
        }
        case 6:
        {
            cout << "请输入一个数：" << endl;
            cin >> a;
            a--;
            linker << a.values << endl;
            break;
        }
        case 7:
        {
            cout << "请输入一个数：" << endl;
            cin >> a;
            a.transform();
            break;
        }
        default:
        {
            cout << "输出有误!" << endl; break;
        }
        }

    }
    cout << endl;

}
int App::GetStart()
{
    while (true) {
        cout << "按回车键继续，w键退出系统!" << endl;
        char ch = getchar();
        if (ch == '\n') {
            system("cls");//调用系统命令完成清屏操作
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