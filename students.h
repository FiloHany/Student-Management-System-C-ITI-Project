#include"STD_Types.h"
// Struct contain numbers of students
typedef struct Student{

    u8 name[50];
    u16 ID ;
    f32 grades[5];
    f32 avg ;
    u8 status[10];

}Student;

//check if id is already exsist
u8 idExists(Student *ptr, u8 count1, u8 idToCheck);

//Input function
void inputStudent(Student **ptr);

//Calculate Average Function
void AVG(Student *ptr);

//Determine Pass/Fail Function
void passing(Student *ptr);

//Display function
void Display(Student *ptr);

//Search Function
void Search(Student *ptr, u8 ID);

//Search Function
void Update(Student *ptr, u8 ID);

// Function to delete a student's record
void Delete(Student **ptr, u8 ID);
