import jax
import jax.numpy as jnp
import jax.random as random
from functools import partial
import time
STRIKE = 100.
SPOT = 100.
VOL = 0.3
RATE = 0.03
T = 1.
NUMSTEPS = 300
NUMPATHS = int(1E7)
dt = T / NUMSTEPS
dt2 = dt ** 0.5

@partial(jax.jit, static_argnames=["num_steps"])
def montecarlo_simulation(key, S0, mu, sigma, T, num_steps):

    dt = T / num_steps
    # initial_state = (S0 * jnp.ones(num_simulations), dt, mu, sigma)
    key, subkey = random.split(key)
    z = random.normal(subkey, shape=(num_steps,))

    def montecarlo_step(carry, zi):
        S_new = carry * jnp.exp((mu - 0.5 * sigma ** 2) * dt + sigma * dt2 * zi)
        return S_new, S_new

    _, path = jax.lax.scan(montecarlo_step, S0, z)

    return path

t1 = time.time()
# Generate random keys
rng_key = random.PRNGKey(0)
rng_keys = jax.random.split(rng_key, NUMPATHS)  # (nchains,)
montecarlo_vmap = jax.vmap(montecarlo_simulation, in_axes=((0,) + (None,)*5), out_axes=1)
# Run simulation
S = montecarlo_vmap(rng_keys, SPOT, RATE, VOL, T, NUMSTEPS)
t2 = time.time()
duration = t2 - t1
print(f"Totalpaths: {NUMPATHS}")
print(f"Duration(seconds): {duration}")
