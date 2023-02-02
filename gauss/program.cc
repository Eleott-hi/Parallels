#include "program.h"

#include "console.h"
#include "lib/gauss.h"
#include "timer.h"

namespace s21 {

void Program::Exec() {
  Matrix matrix = Console::ReadMatrix("A");
  if (matrix.Cols() != matrix.Rows() + 1 || matrix.Rows() <= 0) {
    Console::Error("Incorrect matrix size");
    return;
  }

  const int number_of_iterations =
      Console::ReadInt("Enter number of iterations:\n> ");

  if (number_of_iterations < 1) {
    Console::Error("N can not be less than 1");
    return;
  }

  Timer timer;
  std::vector<double> result;

  timer.Start();
  for (size_t n = 0; n < number_of_iterations; ++n)
    result = Gauss::SolveOneThread(matrix);
  Console::WriteVector(result, "Answers: ");
  Console::WriteLine("Single thread execution time: " +
                     std::to_string(timer.Finish()) + "[ms]");

  timer.Start();
  for (size_t n = 0; n < number_of_iterations; ++n)
    result = Gauss::SolveMultiThread(matrix);
  Console::WriteVector(result, "Answers: ");
  Console::WriteLine("Multi thread execution time: " +
                     std::to_string(timer.Finish()) + "[ms]");
}

}  // namespace s21
