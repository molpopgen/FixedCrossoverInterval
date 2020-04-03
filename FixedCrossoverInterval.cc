#include <fwdpp/genetic_map/genetic_map_unit.hpp>
#include <pybind11/pybind11.h>
#include <pybind11/functional.h>
#include <gsl/gsl_randist.h>

struct fixed_crossover_interval : public fwdpp::genetic_map_unit
{
    const double start, stop;
    const unsigned num_xovers;
    fixed_crossover_interval(double start_, double stop_, unsigned nxovers)
        : fwdpp::genetic_map_unit(), start(start_), stop(stop_), num_xovers(nxovers)
    {
    }

    void
    operator()(const gsl_rng *r, std::vector<double> &breakpoints) const final
    {
        for (unsigned i = 0; i < num_xovers; ++i)
            {
                breakpoints.push_back(gsl_ran_flat(r, start, stop));
            }
    }

    std::unique_ptr<fwdpp::genetic_map_unit>
    clone() const final
    {
        return std::unique_ptr<fixed_crossover_interval>(
            new fixed_crossover_interval(start, stop, num_xovers));
    }
};

PYBIND11_MODULE(FixedCrossoverInterval, m)
{
    pybind11::object python_base_class
        = pybind11::module::import("fwdpy11"); //.attr("GeneticMapUnit");

    pybind11::class_<fixed_crossover_interval, fwdpp::genetic_map_unit>(
        m, "FixedCrossoverInterval")
        .def(pybind11::init<double, double, unsigned>(), pybind11::arg("start"),
             pybind11::arg("stop"), pybind11::arg("num_xovers"))
        .def(pybind11::pickle(
            [](const fixed_crossover_interval &self) {
                return pybind11::make_tuple(self.start, self.stop, self.num_xovers);
            },
            [](pybind11::tuple t) {
                return std::unique_ptr<fixed_crossover_interval>(
                    new fixed_crossover_interval(t[0].cast<double>(),
                                                 t[1].cast<double>(),
                                                 t[2].cast<unsigned>()));
            }));
}
