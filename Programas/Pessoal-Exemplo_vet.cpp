/***************************************
* O que é Map em C++?
* Exemplo #1 - Uso de Map, find e erase
***************************************/
#include <iostream>
#include <vector>
#include <map>
 
using namespace std;
 
int main() {
    std::map<const string, unsigned int> aStudentsGradesMap = {{"João", 9}, {"Maria", 10}, {"Diego", 7.7}, {"Carla", 8.0}, {"Marcos", 0}};
     
    // Nota que as chaves dos elementos de um map são sempre const
    for (const std::pair<const string, unsigned int>& aStudentGradePair : aStudentsGradesMap)
    {
        // first guarda o nome do aluno, e second guarda sua nota
        cout << "Aluno(a)/Nota: " << aStudentGradePair.first << ", " << aStudentGradePair.second << endl;
    }
     
    // Remoção do elemento cuja chave é Marcos do map
    aStudentsGradesMap.erase("Marcos");
    // Adição de um novo elemento com chave Enzo e valor mapeado 5 ao map
    aStudentsGradesMap["Enzo"] = 5;
    cout << "\n-----------------------------------" << endl;
    cout << "Marcos foi expulso do colégio :(" << endl;
    cout << "Enzo foi matriculado do colégio :)" << endl;
    cout << "\n-----------------------------------" << endl;
    cout << "Alunos matriculados:" << endl;
     
    // Forma equivalente de se usar o for com map em C++.
    // O auto torna a declaração da variável do loop muito mais concisa.
    for (const auto& aStudentGradePair : aStudentsGradesMap)
    {
        cout << aStudentGradePair.first << endl;
    }
     
    cout << "\n-----------------------------------" << endl;
    if (aStudentsGradesMap.find("Marcos") == aStudentsGradesMap.end())
    {
        cout << "Onde está Marcos?" << endl;
    }
     
    return 0;
}

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        int searched;
        for (int i=0;i<nums.size();i++){
            searched = target-nums[i];
            for (int j=0;j<nums.size();j++){
                if (i!=j){
                    if (nums[j]==target-nums[i]){
                        return {i,j};
                    }
                }  
            }
        }
        return {};
    }
};