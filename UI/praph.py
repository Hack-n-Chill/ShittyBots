import matplotlib.pyplot as plt
import numpy as np

x = np.linspace( 0,10 )

for n in range(3):
    y = np.sin( x+n )
    plt.figure()
    plt.plot( x, y )
    plt.savefig('myfilename%03d.png'%(n))