#ifndef A3_SRC_ANT_LIB_ANT_H_
#define A3_SRC_ANT_LIB_ANT_H_

#include <vector>

#include "matrix.h"
#include "thread_pool.h"

namespace s21 {

class Ant {
 public:
  struct TsmResult {
    std::vector<int> vertices;
    double distance;
  };

  static TsmResult SolveTravelingSalesmanProblem(const Matrix& graph, size_t N,
                                                 bool multi = false);

 private:
  static bool IsMatrixCorrect(const Matrix& graph);

  static TsmResult& Convert(TsmResult& res);

  static std::vector<double> RunColony(int ants, const Matrix& graph,
                                       const std::vector<double>& desires,
                                       TsmResult& best);
  static std::vector<double> RunColonyMulti(int ants, const Matrix& graph,
                                            const std::vector<double>& desires,
                                            TsmResult& best, ThreadPool& pool);

  static TsmResult Route(int city_from, const Matrix& graph,
                         const std::vector<double>& desires);

  static void UpdatePheromone(std::vector<double>& pheromone,
                              const std::vector<double>& delta_pheromone,
                              double evaporation = 0.5);

  static void UpdateDeltaPheromone(std::vector<double>& delta_pheromone,
                                   const TsmResult& route, int size,
                                   double q = 100);

  static std::vector<double> CalcDesires(const Matrix& graph,
                                         const std::vector<double>& pheromone,
                                         double alpha = 1, double beta = 4);

  static double Random();
};

}  // namespace s21

#endif  // A3_SRC_ANT_LIB_ANT_H_
