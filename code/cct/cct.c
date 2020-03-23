
// checks if given cct is inside of the given entity
// returns true if true, else if not
var is_cct_in_rect(ENTITY *cct, ENTITY *rect, var scale_)
{
    if (!cct)
    {
        error("Can't perform cct_vs_rect check! CCT entity doesn't exist!");
        return;
    }

    if (!rect)
    {
        error("Can't perform cct_vs_rect check! Rect entity doesn't exist!");
        return;
    }

    VECTOR pos;
    vec_diff(&pos, &cct->x, &rect->x);
    vec_rotateback(&pos, &rect->pan);
    vec_add(&pos, &rect->x);

    var delta_x = pos.x - maxv(rect->x + (rect->min_x * scale_), minv(pos.x, rect->x + (rect->max_x * scale_)));
    var delta_y = pos.y - maxv(rect->y + (rect->min_y * scale_), minv(pos.y, rect->y + (rect->max_y * scale_)));
    var rect_delta = (delta_x * delta_x) + (delta_y * delta_y);

    var cct_top = cct->z + (cct->max_z * scale_);
    var cct_bottom = cct->z + (cct->min_z * scale_);
    var cct_z_hit = false;

    if ((rect->z + rect->min_z) - cct_top > 0 || cct_bottom - (rect->z + rect->max_z) > 0)
    {
        cct_z_hit = true;
    }

    if (rect_delta < (cct->max_x * cct->max_x) && cct_z_hit == false)
    {
        return true;
    }

    return false;
}