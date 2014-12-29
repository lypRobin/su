/*      Dust.cpp
 *
 *      Copyright (C) 2014  Yanpeng Li <lyp40293@gmail.com>
 *
 *      This program is free software; you can redistribute it and/or modify
 *      it under the terms of the GNU General Public License as published by
 *      the Free Software Foundation; either version 2 of the License, or
 *      (at your option) any later version.
 *
 *      This program is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *      GNU General Public License for more details.
 *
 *      You should have received a copy of the GNU General Public License
 *      along with this program; if not, write to the Free Software
 *      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 *      MA 02110-1301, USA.
 */

#include "Dust.h"

Dust::Dust(int pin):Device(pin)
{
	m_lo = 0;
	m_result = 0;
	m_time = millis();
}

int Dust::get(char *buf, size_t size)
{
	item_t res = itemNew();
	unsigned long time = millis();

	m_lo += pulseIn(getIndex(), LOW);
	if((time - m_time) >= DUST_INTERVAL) {
		float r = m_lo / (DUST_INTERVAL * 10.0);
		m_result = (int)(1.1 * pow(r, 3) - 3.8 * pow(r, 2) + 520 * r + 0.62);
		m_time = time;
		m_lo = 0;
	}
	res += item("CF", String(m_result));
	return itemGet(res, buf, size);
}
