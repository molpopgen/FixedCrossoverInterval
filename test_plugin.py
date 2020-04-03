import fwdpy11
print(fwdpy11.__file__)
import numpy as np
import FixedCrossoverInterval

N = 1000

pdict = {'demography': fwdpy11.DiscreteDemography(),
         'simlen': 100,
         'nregions': [],
         'sregions': [fwdpy11.GaussianS(0, 1, 1, 0.25)],
         'recregions': [FixedCrossoverInterval.FixedCrossoverInterval(0, 1, 2)],
         'rates': (0., 5e-3, None),
         'gvalue': fwdpy11.Additive(2., fwdpy11.GSS(VS=1, opt=1)),
         'prune_selected': False
         }

params = fwdpy11.ModelParams(**pdict)

print(params.recregions)

pop = fwdpy11.DiploidPopulation(N, 1.0)

rng = fwdpy11.GSLrng(42)

fwdpy11.evolvets(rng, pop, params, 100)

