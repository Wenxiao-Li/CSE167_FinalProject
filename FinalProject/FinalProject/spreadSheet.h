/*
#include "sphere.h"

class spreadSheet : public Geometry{
	public:
		Geometry** list;
		int list_size;

		spreadSheet() {}
		spreadSheet(Geometry** l, int n) {
			list = l;
			list_size = n;
		}
		bool hit(ray& r, float t_max, hit_record& rec) const;
};

bool spreadSheet::hit(ray& r, float t_max, hit_record& rec) const {
	hit_record curRecord;
	bool hasHit = false;
	float closest = t_max;
	for (int i = 0; i < list_size; i++) {
		if (list[i]->hit(r, closest, curRecord)) {
			hasHit = true;
			closest = curRecord.t;
			rec = curRecord;
		}
	}

	return hasHit;
}
*/