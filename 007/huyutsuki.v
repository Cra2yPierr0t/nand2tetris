module huyutsuki(sw2, sw3, cut_pwm_base_max);
    input sw2, sw3;
    output [15:0] cut_pwm_base_max;

    reg [15:0] cut_pwm_base_max = 16'b0000000000000000;

    assign cup_pwm_base_max = selector(sw2, sw3);

    function [15:0] selector(input sw2, sw3);
        if(sw2 == 1) begin
            selector = cut_pwm_base_max - 50;
        end else if(sw3 == 1) begin
            selector = cut_pwm_base_max + 50;
        end else begin
            selector = cut_pwm_base_max;
        end
    endfunction
            

    /* always @(posedge sw2) begin
        cut_pwm_base_max = cut_pwm_base_max - 50;
    end

    always @(posedge sw3) begin
        cut_pwm_base_max = cut_pwm_base_max + 50;
    end */
endmodule
