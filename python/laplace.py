#!/usr/bin/python3

from math import log
from random import random

def exp_sample(mean):
    return -mean*log(random())

def laplace(scale):
    e1 = exp_sample(scale)
    e2 = exp_sample(scale)
    print("1st exponential : ", e1)
    print("2nd exponential : ", e2)
    return e1 - e2

print("Laplase noise with scale 1 : " , laplace(1))
print("Laplase noise with scale 0.7 : " , laplace(0.7))
print("Laplase noise with scale 0.5 : " , laplace(0.5))
