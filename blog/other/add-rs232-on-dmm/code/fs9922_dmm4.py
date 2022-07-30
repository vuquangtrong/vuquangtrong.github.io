import serial

##########
def parse(data):
    try:
        # print(data.hex(' '), end=' >> ')
        
        sign = 1 if data[0]==0x2b else -1
        
        digit1 = data[1]-0x30
        digit2 = data[2]-0x30
        digit3 = data[3]-0x30
        digit4 = data[4]-0x30

        decimal = 1
        match data[6]:
            case 0x30:
                decimal = 1
            case 0x31:
                decimal = 1000
            case 0x32:
                decimal = 100
            case 0x34:
                decimal = 10

        if data[1] == 0x3f:
            if sign == 1:
                value = float('inf')
            else:
                value = float('-inf')
        else:
            value = sign * (digit1*1000 + digit2*100 + digit3*10 + digit4) / decimal
        
        range = 'auto'  if data[7] & (1 << 5) else 'man'
        dc    = 'DC'    if data[7] & (1 << 4) else ''
        ac    = 'AC'    if data[7] & (1 << 3) else ''
        rel   = 'REL'   if data[7] & (1 << 2) else ''
        hold  = 'HOLD'  if data[7] & (1 << 1) else ''
        bpn   = 'BPN'   if data[7] & (1 << 0) else ''
        
        u     = 'u'     if data[9] & (1 << 7) else ''
        m     = 'm'     if data[9] & (1 << 6) else ''
        k     = 'k'     if data[9] & (1 << 5) else ''
        M     = 'M'     if data[9] & (1 << 4) else ''
        diode = 'D'     if data[9] & (1 << 2) else ''
        duty  = '%'     if data[9] & (1 << 1) else ''
        
        vol   = 'V'     if data[10] & (1 << 7) else ''
        amp   = 'A'     if data[10] & (1 << 6) else ''
        ohm   = 'Ω'     if data[10] & (1 << 5) else ''
        hz    = 'Hz'    if data[10] & (1 << 3) else ''
        far   = 'F'     if data[10] & (1 << 2) else ''
        tC    = '°C'    if data[10] & (1 << 1) else ''
        tF    = '°F'    if data[10] & (1 << 0) else ''
        
    except:
        value = float('inf')

    else:
        print(f'{range} {dc}{ac} {value:+} {u}{m}{k}{M}{vol}{amp}{ohm}{far}{hz}{duty}{tC}{tF}')
        return value


##########
if __name__ == '__main__':
    # open and read
    with serial.Serial('COM5', 2400) as dmm:
        while True:
            try:
                line = dmm.readline()
                print(parse(line))
            except KeyboardInterrupt:
                break