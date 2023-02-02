#include "ant.h"

#include <algorithm>
#include <random>

namespace s21 {

Ant::TsmResult Ant::SolveTravelingSalesmanProblem(const Matrix& graph, size_t N,
                                                  bool multi) {
  if (!IsMatrixCorrect(graph)) return {{}, -1};

  int cities = graph.Rows();
  const int ants = cities;
  std::vector<double> pheromone(cities * cities, 0.2);
  TsmResult best = {{}, std::numeric_limits<double>::infinity()};
  ThreadPool pool(multi ? std::thread::hardware_concurrency() : 0);

  for (int n = 0; n < N; ++n) {
    std::vector<double> desires = CalcDesires(graph, pheromone);
    std::vector<double> delta_pheromone =
        multi ? RunColonyMulti(ants, graph, desires, best, pool)
              : RunColony(ants, graph, desires, best);
    UpdatePheromone(pheromone, delta_pheromone);
  }

  return Convert(best);
}

bool Ant::IsMatrixCorrect(const Matrix& graph) {
  int size = graph.Rows();
  if (size != graph.Cols() || size == 0) return false;
  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {
      if (i == j) continue;
      if (graph(i, j) <= 0) return false;
    }
  }
  return true;
}

Ant::TsmResult& Ant::Convert(TsmResult& res) {
  std::for_each(res.vertices.begin(), res.vertices.end(),
                [](auto& i) { i += 1; });
  return res;
}

std::vector<double> Ant::RunColonyMulti(int ants, Matrix const& graph,
                                        std::vector<double> const& desires,
                                        TsmResult& best, ThreadPool& pool) {
  int size = graph.Rows();
  std::vector<double> delta_pheromone(size * size, 0);
  std::mutex mtx;

  auto func = [&mtx, &best, &delta_pheromone, &graph, &desires](size_t ant) {
    TsmResult route = Route(ant, graph, desires);

    std::scoped_lock<std::mutex> lock(mtx);
    best = route.distance < best.distance ? route : best;
    UpdateDeltaPheromone(delta_pheromone, route, graph.Rows());
  };

  for (int ant = 0; ant < ants; ++ant) pool.AddTask(func, ant);

  pool.WaitAll();
  return delta_pheromone;
}

std::vector<double> Ant::RunColony(int ants, Matrix const& graph,
                                   std::vector<double> const& desires,
                                   TsmResult& best) {
  int size = graph.Rows();
  std::vector<double> delta_pheromone(size * size, 0);

  for (int ant = 0; ant < ants; ++ant) {
    TsmResult route = Route(ant, graph, desires);
    best = route.distance < best.distance ? route : best;
    UpdateDeltaPheromone(delta_pheromone, route, size);
  }

  return delta_pheromone;
}

Ant::TsmResult Ant::Route(int city_from, const Matrix& graph,
                          const std::vector<double>& desires) {
  int cities = graph.Rows();

  std::vector<int> vertices;
  std::vector<bool> visited(cities, false);
  double distance = 0;
  int start = city_from;

  for (int i = 0; i < cities; ++i) {
    double desires_sum = 0;
    visited[city_from] = true;
    vertices.push_back(city_from);
    std::vector<double> preference(cities, 0);

    for (int city_to = 0; city_to < cities; ++city_to) {
      if (visited[city_to]) continue;
      int index = city_from * cities + city_to;
      desires_sum += desires[index];
    }

    double random = Random();
    double desire = 0;

    for (int city_to = 0; city_to < cities; ++city_to) {
      if (visited[city_to]) continue;
      int index = city_from * cities + city_to;
      desire += desires[index] / desires_sum;
      if (random <= desire) {
        distance += graph(city_from, city_to);
        city_from = city_to;
        break;
      }
    }
  }

  distance += graph(vertices.back(), start);
  vertices.push_back(start);

  return {vertices, distance};
}

void Ant::UpdatePheromone(std::vector<double>& pheromone,
                          const std::vector<double>& delta_pheromone,
                          double evaporation) {
  double remainder_percentage = 1 - evaporation;
  for (size_t i = 0; i < pheromone.size(); ++i) {
    pheromone[i] *= remainder_percentage;
    pheromone[i] += delta_pheromone[i];
  }
}

void Ant::UpdateDeltaPheromone(std::vector<double>& delta_pheromone,
                               const TsmResult& route, int size, double q) {
  auto const& [vertices, distance] = route;

  for (size_t i = 0; i < vertices.size() - 1; ++i) {
    int index = vertices[i] * size + vertices[i + 1];
    delta_pheromone[index] += q / distance;
  }
}

std::vector<double> Ant::CalcDesires(const Matrix& graph,
                                     const std::vector<double>& pheromone,
                                     double alpha, double beta) {
  int size = graph.Rows();
  std::vector<double> desires(size * size, 0);

  for (int i = 0; i < size; ++i)
    for (int j = 0; j < size; ++j) {
      if (i == j) continue;
      int index = i * size + j;
      double pheromone_part = pow(pheromone[index], alpha);
      double weight_part = pow(1. / graph(i, j), beta);

      desires[index] = pheromone_part * weight_part;
      if (desires[index] == 0)
        desires[index] = std::numeric_limits<double>::min();
    }

  return desires;
}

double Ant::Random() {
  std::random_device rd;
  std::uniform_real_distribution<double> uniform_dist(0, 1);

  return uniform_dist(rd);
}

}  // namespace s21
