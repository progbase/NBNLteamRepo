enum GARAGE_PROTOCOL{
    GET_PERSON_MOTION_STATUS, // expects to receive a 1 - there is motion, 0 - there is no motion
    GET_CAR_MOTION_STATUS, // expects to receive a 1 - there is a car moving, 0 - there is no car moving
    GET_CAR_PRESENCE_STATUS, // expects to receive a 1 - there is a car in the garage, 0 - there is not
    GET_DOOR_STATUS, // expects to receive 1 - the door is opened, 0 - the door is closed
	SET_DOOR_OPEN, // expects to receive 1 if opening, 0 if already
	SET_DOOR_CLOSE // expects to receive 1 if closing, 0 if already
};
