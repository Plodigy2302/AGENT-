#include "Assignment.h"
#include "Course.h"
#include "Department.h"
#include "Enrollment.h"
#include "Instructor.h"
#include "Student.h"

#include "CircularQueue.h"
#include "DoublyLinkedList.h"
#include "SinglyLinkedList.h"

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

int main() {
    std::cout << "==============================\n";
    std::cout << "   Sistema de Gestión Educativa\n";
    std::cout << "==============================\n\n";

    SinglyLinkedList<Student> estudiantes;
    estudiantes.push_back(Student{1, "Ana Morales", "ana@uni.edu", "Ingeniería"});
    estudiantes.push_back(Student{2, "Luis Torres", "luis@uni.edu", "Diseño"});
    estudiantes.push_back(Student{3, "María Rojas", "maria@uni.edu", "Medicina"});

    estudiantes.for_each([](Student &est) {
        if (est.id() == 1) {
            est.record_grade("COMP101", 18.5);
            est.record_grade("MAT205", 17.0);
        } else if (est.id() == 2) {
            est.record_grade("DIS210", 15.0);
            est.record_grade("MAT205", 14.5);
        } else {
            est.record_grade("BIO120", 19.0);
            est.record_grade("QUI130", 18.0);
        }
    });

    DoublyLinkedList<Course> cursos;
    cursos.push_front(Course{"COMP101", "Programación I", 4, 101});
    cursos.push_front(Course{"MAT205", "Cálculo Multivariable", 5, 102});
    cursos.push_front(Course{"DIS210", "Teoría del Color", 3, 103});
    cursos.push_front(Course{"BIO120", "Biología Celular", 4, 104});

    cursos.insert_after(
        [](const Course &curso) { return curso.code() == "COMP101"; },
        [](const Course &curso) {
            return Course{curso.code() + "-L", "Laboratorio de " + curso.title(), curso.credits(), curso.instructor_id()};
        });

    cursos.cocktail_sort([](const Course &a, const Course &b) { return a.code() < b.code(); });

    CircularQueue<Assignment> bandeja_tareas(5);
    bandeja_tareas.enqueue(Assignment{"Proyecto Final", "Desarrollar un LMS", "2023-11-30"});
    bandeja_tareas.enqueue(Assignment{"Ensayo", "Impacto del e-learning", "2023-10-12"});
    bandeja_tareas.enqueue(Assignment{"Quiz", "Unidad 3", "2023-09-21"});

    bandeja_tareas.rotate(1);

    estudiantes.sort([](const Student &a, const Student &b) {
        return a.calculate_gpa() > b.calculate_gpa();
    });

    estudiantes.remove_if([](const Student &est) { return est.calculate_gpa() < 15.0; });

    std::vector<Instructor> instructores = {
        Instructor{101, "Julio Pérez", "julio@uni.edu", "Computación"},
        Instructor{102, "Claudia Vega", "claudia@uni.edu", "Matemática"},
        Instructor{103, "Pablo Díaz", "pablo@uni.edu", "Diseño"},
        Instructor{104, "Rosa Aguilar", "rosa@uni.edu", "Ciencias"},
    };

    instructores[0].assign_course("COMP101");
    instructores[0].assign_course("COMP101-L");
    instructores[1].assign_course("MAT205");
    instructores[2].assign_course("DIS210");
    instructores[3].assign_course("BIO120");

    Department comp("Computación");
    comp.add_instructor(101);
    comp.add_instructor(105);

    bool activo = true;
    while (activo) {
        std::cout << "\nSeleccione una opción:\n";
        std::cout << "1. Ver ranking de estudiantes\n";
        std::cout << "2. Consultar cursos disponibles\n";
        std::cout << "3. Revisar bandeja de tareas\n";
        std::cout << "4. Ver instructores por departamento\n";
        std::cout << "0. Salir\n> ";

        int opcion;
        if (!(std::cin >> opcion)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Entrada inválida.\n";
            continue;
        }

        switch (opcion) {
        case 1: {
            std::cout << "\nEstudiantes destacados:\n";
            std::cout << std::left << std::setw(15) << "Nombre" << std::setw(10) << "GPA" << '\n';
            std::cout << "-----------------------------\n";
            estudiantes.for_each([](const Student &est) {
                std::cout << std::left << std::setw(15) << est.name() << std::setw(10) << est.calculate_gpa() << '\n';
            });
            break;
        }
        case 2: {
            std::cout << "\nOferta académica (ordenada):\n";
            cursos.for_each_reverse([](const Course &curso) {
                std::cout << "- " << curso.code() << ": " << curso.title() << " (" << curso.credits()
                          << " créditos)" << '\n';
            });
            break;
        }
        case 3: {
            std::cout << "\nTareas pendientes:\n";
            bandeja_tareas.for_each([](const Assignment &tarea) {
                std::cout << "* " << tarea.title() << " -> " << tarea.due_date() << '\n';
            });
            break;
        }
        case 4: {
            std::cout << "\nDepartamento de " << comp.name() << ":\n";
            for (int instructor_id : comp.instructor_ids()) {
                auto it = std::find_if(instructores.begin(), instructores.end(),
                                       [&](const Instructor &doc) { return doc.id() == instructor_id; });
                if (it != instructores.end()) {
                    std::cout << "- " << it->name() << " (" << it->role() << ")\n";
                } else {
                    std::cout << "- Instructor invitado #" << instructor_id << '\n';
                }
            }
            break;
        }
        case 0:
            activo = false;
            break;
        default:
            std::cout << "Opción inválida.\n";
            break;
        }
    }

    std::cout << "\nGracias por utilizar el sistema de gestión educativa." << std::endl;
    return 0;
}
