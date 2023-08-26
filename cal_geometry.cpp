
typedef double db;
const db eps = 1e-9;
inline int sign(db a) {
	return a < -eps ? -1 : a > eps; 
}
inline int cmp(db a, db b){
	return sign(a - b);
}
struct P{
	db x, y;
	P(){}
	P(db _x, db _y) : x(_x), y(_y){}
	P operator+ (P p) { return {x + p.x, y + p.y}; }
	P operator- (P p) { return {x - p.x, y - p.y}; }
	P operator* (db d) { return {x * d, y * d}; }
	P operator/ (db d) { return {x / d, y / d}; }
	
	bool operator< (P p) const{
		int c = cmp(x, p.x);
		if(c) return c == -1;
		return cmp(y, p.y) == -1;	
	}
	bool operator ==(P o) const{
		return cmp(x, o.x) == 0 && cmp(y, o.y) == 0;
	}
	db dot(P p) { return x * p.x + y * p.y; } // ���� 
	db det(P p) { return x * p.y - y * p.x; } // ���� 
	db distTo(P p){ return (*this - p).abs(); } // ������֮��ľ��� 
	double alpha() { return atan2(y, x); } // ��Ƕ�
	long double alphal() {return atan2l(y, x); }
	void read() { cin >> x >> y; }
	void wirte() { cout << "(" << x << "," << y << ")" << "\n"; }
	db abs() { return sqrt(abs2()); } 
	db abs2() { return x * x + y * y; }
	P rot90() { return P(-y, x); }
	P unit() { return *this/abs(); }
	int quad() const {} // to do
	P rot(db an) { return {x * cos(an) - y * sin(an), x * sin(an) + y * cos(an)}; }
	
};
#define cross(p1, p2, p3) ((p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y))
// p1p1 x p1p3
#define crossOp(p1, p2, p3) sign(cross(p1, p2, p3))

// ֱ��p1p2 q1q2 �Ƿ�ǡ��һ������ 
bool chkLL (P p1, P p2, P q1, P q2){ // �ж�����ֱ���Ƿ����ཻ��ϵ 
	db a1 = cross(q1, q2, p1), a2 = -cross(q1, q2, p2);
	return sign(a1 + a2) != 0;
}

P isLL(P p1, P p2, P q1, P q2){
	db a1 = cross(q1, q2, p1), a2 = -cross(q1, q2, p2);
	return (p1 * a2 + p2 * a1) / (a1 + a2);
}
// �ж����� [l1, r1], [l2, r2] �Ƿ��ཻ
bool intersect(db l1, db r1, db l2, db r2){
	if (l1 > r1) swap(l1, r1); if(l2 > r2) swap(l2, r2);
	return !(cmp(r1, l2) == -1 || cmp(r2, l1) == -1); 
}
// �߶��ཻ 
bool isSS(P p1, P p2, P q1, P q2) {
	return intersect(p1.x, p2.x, q1.x, q2.x) && intersect(p1.y, p2.y, q1.y, q2.y)
	&& crossOp(p1, p2, q1) * crossOp(p1, p2, q2) <= 0 && crossOp(q1, q2, p1) * crossOp(q1, q2, p2) <= 0;
	
}
// �߶��ϸ��ཻ
bool isSS_strict(P p1, P p2, P q1, P q2){
	return crossOp(p1, p2, q1) * crossOp(p1, p2, q2) < 0 && crossOp(q1, q2, p1) * crossOp(q1, q2, p2) < 0;	
}
// ��m�ڲ���[a,b]֮�� 
bool isMiddle(db a, db m, db b){
	return sign(a - m) == 0 || sign(b - m) == 0 || (a < m != b < m);
}
// ����m�ڲ��� �� a, b֮�� 
bool isMiddle(P a, P m, P b){
	return isMiddle(a.x, m.x, b.x) && isMiddle(a.y, m.y, b.y);	
}
// ��q�Ƿ����߶� p1p2 �� 
bool onSeg(P p1, P p2, P q){
	return crossOp(p1, p2, q) == 0 && isMiddle(p1, q, p2);	
}
bool onSeg_strict(P p1, P p2, P q){
	return crossOp(p1, p2, q) == 0 && sign((q-p1).dot(p1-p2)) * sign((q - p2).dot(p1 - p2)) < 0;
}
// �� q �� ֱ��p1p2��ͶӰ 
P proj( P p1, P p2, P q){
	P dir = p2 - p1;
	return p1 + dir * (dir.dot(q - p1) / dir.abs2());
}
// �� �� ֱ�� p1p2Ϊ��ķ��� 
P reflect(P p1, P p2, P q){
	return proj(p1, p2, q) * 2 - q; 	
}
// �� q ���߶� p1p2����С���� 
db nearest(P p1, P p2, P q){
	if(p1 == p2) return p1.distTo(q);
	P h = proj(p1, p2, q);
	if(isMiddle(p1, h, p2))
		return q.distTo(h);
	return min(p1.distTo(q), p2.distTo(q)); 
}
// ���߶� p1p2 q1q2 �ľ��� 
db disSS(P p1, P p2, P q1, P q2){
	if(isSS(p1, p2, q1, q2)) return 0;
	return min(min(nearest(p1, p2, q1), nearest(p1, p2, q2)), min(nearest(q1, q2, p1), nearest(q1, q2, p2)));
}
