#include "program.h"

#include "console.h"
#include "lib/ant.h"
#include "timer.h"

namespace s21 {

void Program::Exec() {
  Matrix matrix = Console::ReadMatrix("");
  if (matrix.Cols() != matrix.Rows() || matrix.Cols() <= 0) {
    Console::Error("Incorrect graph size");
    return;
  }

  const int number_of_iterations =
      Console::ReadInt("Enter number of iterations:\n> ");

  if (number_of_iterations < 1) {
    Console::Error("N can not be < 1");
    return;
  }

  Timer timer;

  timer.Start();
  Ant::TsmResult result =
      Ant::SolveTravelingSalesmanProblem(matrix, number_of_iterations);
  Console::WriteVector(std::vector<double>{result.distance}, "Distance: ");
  Console::WriteVector(result.vertices, "Vertices: ");
  Console::WriteLine("Single thread execution time: " +
                     std::to_string(timer.Finish()) + "[ms]");

  timer.Start();
  result =
      Ant::SolveTravelingSalesmanProblem(matrix, number_of_iterations, true);
  Console::WriteVector(std::vector<double>{result.distance}, "Distance: ");
  Console::WriteVector(result.vertices, "Vertices: ");
  Console::WriteLine("Multi thread execution time: " +
                     std::to_string(timer.Finish()) + "[ms]");
}

}  // namespace s21
