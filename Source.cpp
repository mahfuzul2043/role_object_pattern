#include <iostream>
#include <string>
#include <vector>

using namespace std;

class EmployeeRole;
class Employee {
public:
	virtual void addRole(EmployeeRole* role) = 0;
	virtual void removeRole(string roleName) = 0;
	virtual bool hasRole(string roleName) = 0;
	virtual EmployeeRole* getRole(string roleName) = 0;
};

class EmployeeRole {
private:
	string roleName;
public:
	virtual ~EmployeeRole() {}
	string getRoleName() {
		return roleName;
	}
	void setRoleName(string roleName) {
		this->roleName = roleName;
	}
};

class EmployeeCore : public Employee {
private:
	vector<EmployeeRole*> roles;
	string name;
public:
	EmployeeCore() {}
	EmployeeCore(string name) {
		this->name = name;
	}
	void addRole(EmployeeRole* role) {
		roles.push_back(role);
	}
	void removeRole(string roleName) {
		for (int i = 0; i < roles.size(); i++) {
			if (roles.at(i)->getRoleName() == roleName) roles.erase(roles.begin() + i);
		}
	}
	bool hasRole(string roleName) {
		for (int i = 0; i < roles.size(); i++) {
			if (roles.at(i)->getRoleName() == roleName) return true;
		}
		return false;
	}
	EmployeeRole* getRole(string roleName) {
		if (hasRole(roleName)) {
			for (int i = 0; i < roles.size(); i++) {
				if (roles.at(i)->getRoleName() == roleName) return roles.at(i);
			}
		}
		return nullptr;
	}
	void printRoles() {
		for (EmployeeRole* role : roles) {
			cout << role->getRoleName() << endl;
		
		}
	}
	string getName() {
		return name;
	}
};

class SalesRep : public EmployeeRole {
private:
	int numSales;
public:
	SalesRep() {
		setRoleName("SalesRep");
	}
	void setNumSales(int numSales) {
		this->numSales = numSales;
	}
	int getNumSales() {
		return numSales;
	}
};

class InventoryStocker : public EmployeeRole {
private:
	int batchesComplete;
public:
	InventoryStocker() {
		setRoleName("InventoryStocker");
	}
	void setBatchesComplete(int numBatches) {
		this->batchesComplete = numBatches;
	}
	int getBatchesComplete() {
		return batchesComplete;
	}
};

int main() {
	EmployeeCore emp1("John");
	SalesRep* role1 = new SalesRep;
	InventoryStocker* role2 = new InventoryStocker;

	emp1.addRole(dynamic_cast<EmployeeRole*>(role1));
	emp1.addRole(dynamic_cast<EmployeeRole*>(role2));
	emp1.printRoles();
	cout << endl;

	role1->setNumSales(25);
	role2->setBatchesComplete(10);

	SalesRep* temp = dynamic_cast<SalesRep*>(emp1.getRole("SalesRep"));
	InventoryStocker* temp2 = dynamic_cast<InventoryStocker*>(emp1.getRole("InventoryStocker"));
	cout << emp1.getName() << " made " << temp->getNumSales() << " sales." << endl;
	cout << emp1.getName() << " completed " << temp2->getBatchesComplete() << " batches of inventory." << endl;

	emp1.removeRole("InventoryStocker");
	cout << endl;
	emp1.printRoles();


	system("pause");
	return 0;
}