import HalfEdge
import math
from Vector3D import *


class Vertex(object):
    """
    initialize the variables
    p the position
    out a out HalfEdge of all
    n the in/out degree
    index
    """
    def __init__(self, p=Vector3D(), out=None, n=0, index=0, normal=Vector3D()):
        self.p = p
        self.out = out
        self.n = n
        self.index = index
        self.normal = normal
        self.isnormal = False

    def __repr__(self):
        return self.p.__repr__()

    def get_normal(self):
        if not self.isnormal:
            self.normal = Vector3D()
            e = self.out
            for i in range(self.n):
                faceAngle = math.acos(max(-1.0, Vector3D.dot_product(
                    (e.target.p - self.p).normalized(),
                    (e.ph.source.p - self.p).normalized()
                )))
                if e.polygon:
                    self.normal += e.polygon.get_normal() * faceAngle
                e = e.ph.th

            self.normal.normalize()
            self.isnormal = True
        return self.normal


if __name__ == '__main__':
    v = Vertex(Vector3D(0,0,0))
    print(v)