import random
import matplotlib.pyplot as plt
import pandas as pd
from math import fabs
import numpy as np

sex_differences = []
pair_differences = []

for i in range(2, 100):
    for j in range(i):
        men = j
        women = i - j
        homo_pair = 0
        hetero_pair = 0

        for m in range(men):
            men = men - 1
            if random.randint(1,i) <= j:
                men = men - 1
                homo_pair = homo_pair + 1
            else:
                women = women - 1
                hetero_pair = hetero_pair + 1
        homo_pair = homo_pair + women // 2

        sex_difference = fabs(2*j - i) / i
        sex_differences.append(sex_difference)

        pair_difference = homo_pair / (homo_pair + hetero_pair)
        pair_differences.append(pair_difference)

plt.scatter(x=pair_differences, y=sex_differences, color='blue', label='generated characteristic')


darwin_output = pd.read_csv('output/logs.csv', sep=';')
darwin_sex_differences = np.fabs((np.array(darwin_output.adult_males_number.tolist()) - np.array(darwin_output.adult_females_number.tolist())) / (np.array(darwin_output.adult_males_number.tolist()) + np.array(darwin_output.adult_females_number.tolist())))
darwin_pair_differences = np.array(darwin_output.homo_couples_number.tolist()) / (np.array(darwin_output.homo_couples_number.tolist()) + np.array(darwin_output.straight_couples_number.tolist()))

plt.scatter(x=darwin_pair_differences, y=darwin_sex_differences, color='red', label='actual results')

plt.title('Sex difference')
plt.xlabel('How many more homosexual couples there are')
plt.ylabel('Difference in number of adults of a given sex')
plt.legend(loc=2)
plt.show()
