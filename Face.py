from Vector3D import *
import HalfEdge


class Face(object):
    """
    initialize the variables
    side a side HalfEdge
    n the HalfEdge number
    index
    normal the normal Vector3D
    """
    def __init__(self, side=None, n=0, index=0, normal=Vector3D()):
        self.side = side
        self.n = n
        self.index = index
        self.normal = normal
        self.isnormal = False
        self.area = 0
        self.isarea = False

    def set_normal(self):
        h = self.side
        self.normal = Vector3D()
        for i in range(self.n):
            self.normal += Vector3D.cross_product(h.nh.target.p - h.target.p, h.source.p - h.target.p)
            h = h.nh
        self.normal.normalize()
        self.isnormal = True

    def get_normal(self):
        if not self.isnormal:
            self.set_normal()
        return self.normal

    def get_triangle_area(self):
        if not self.isarea:
            h1 = self.side
            h2 = h1.nh
            v1 = h1.target.p - h1.source.p
            v2 = h2.target.p - h1.source.p
            self.area = abs(Vector3D.cross_product(v1, v2).length * 0.5)
            self.isarea = True
        return self.area