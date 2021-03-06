-- Copyright © 2008-2014 Pioneer Developers. See AUTHORS.txt for details
-- Licensed under the terms of CC-BY-SA 3.0. See licenses/CC-BY-SA-3.0.txt

define_ship {
	name='Malabar',
	ship_class='medium_passenger_transport',
	manufacturer='mandarava_csepel',
	model='malabar',
	forward_thrust = 160e6,
	reverse_thrust = 80e6,
	up_thrust = 70e6,
	down_thrust = 50e6,
	left_thrust = 50e6,
	right_thrust = 50e6,
	angular_thrust = 170e6,

	hull_mass = 700,
	fuel_tank_mass = 2000,
	capacity = 2300,
	max_cargo = 2000,
	max_laser = 2,
	max_missile = 0,
	max_cargoscoop = 1,
	max_engine = 1,
	min_crew = 1,
	max_crew = 8,
	
	-- Exhaust velocity Vc [m/s] is equivalent of engine efficiency and depend on used technology. Higher Vc means lower fuel consumption.
	-- Smaller ships built for speed often mount engines with higher Vc. Another way to make faster ship is to increase fuel_tank_mass.
	effective_exhaust_velocity = 1794e4,
	price = 6128e3,
	hyperdrive_class = 0,
}

