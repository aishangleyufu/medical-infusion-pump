----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    22:07:25 07/27/2015 
-- Design Name: 
-- Module Name:    chuanbin1 - Behavioral 
-- Project Name: 
-- Target Devices: 
-- Tool versions: 
-- Description: 
--
-- Dependencies: 
--
-- Revision: 
-- Revision 0.01 - File Created
-- Additional Comments: 
--
----------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

---- Uncomment the following library declaration if instantiating
---- any Xilinx primitives in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity chuanbin1 is
    Port (SIGNAL F50M:IN STD_LOGIC;
	 din : in  STD_LOGIC;
           pdate : out  STD_LOGIC_VECTOR (15 downto 0));
end chuanbin1;

architecture Behavioral of chuanbin1 is
COMPONENT fenping2
PORT(F50M : in  STD_LOGIC;
           CS : out  STD_LOGIC;
           SCLK : out  STD_LOGIC
			  );
END COMPONENT;

SIGNAL pdate_tmp :STD_LOGIC_VECTOR(15 downto 0);

SIGNAL SCLK :   STD_LOGIC;
SIGNAL  CS :  STD_LOGIC;
begin
u0:fenping2 PORT MAP(F50M=>F50M,SCLK=>SCLK,CS=>CS);
P3:process(SCLK)

variable i:integer range 0 to 15;
begin
if(sclk'event and sclk='1') then
    if(cs='1')then
	 i:=0;
	 else
	 pdate_tmp(15-i)<=din;
	 i:=i+1;
	 end if;
	 end if;
	 end process P3;
	 
P4:PROCESS(SCLK,CS)
BEGIN
IF (SCLK'EVENT AND SCLK='1') THEN
       IF(CS='1') THEN
		 pdate<=pdate_tmp;
		 end if;
end if;
end process p4;
	 end Behavioral;

