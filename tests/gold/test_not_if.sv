module mod (
  output logic a,
  input logic clk,
  input logic rst
);


always_ff @(posedge clk) begin
  if (!rst) begin
    a <= 1'h1;
  end
  else a <= 1'h0;
end
endmodule   // mod

