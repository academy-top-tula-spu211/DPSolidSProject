// DPSolidSProject.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "ProductStore.h"

using namespace std;

class Employee
{
    int id;
    string name;
    float salary;

public:
    string& Name() { return name; }
    float& Salary() { return salary; }
};

class IDatabase
{
public:
    virtual void AddEmployee(Employee employee) = 0;
};

class DatabaseMSSQL : public IDatabase
{
    //
public:
    void AddEmployee(Employee employee) override
    {

    }
};

class DatabaseOracle : public IDatabase
{
    void AddEmployee(Employee employee) override
    {

    }
};

class Report
{
    //
public:
    void EmployeePrint(Employee employee)
    {

    }
};

int main()
{
    IDatabase* db = new DatabaseOracle();
    db->AddEmployee(Employee());

    ProductStoreGood store(new ConsoleProductReader(),
                           new SimpleProductCreate(),
                           new PriceProductValidate(),
                           new FileProductSave());
}
