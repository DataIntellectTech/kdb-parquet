'''
Script used to create 'all_types.parquet'.
Use/modify as needed.
'''

import pyarrow as pa
import pyarrow.parquet as pq
import numpy as np
from datetime import datetime, time, date, timezone

# Create arrays for each column with random values.
data = {
    'double': pa.array([1.23, 4.56, 7.89], type=pa.float64()),
    'float': pa.array([1.2, 3.4, 5.6], type=pa.float32()),
    'str': pa.array(['apple', 'banana', 'cherry']),
    'int32': pa.array([-10, 0, 10], type=pa.int32()),
    'uint16': pa.array([1, 2, 3], type=pa.uint16()),
    'uint32': pa.array([100, 200, 300], type=pa.uint32()),
    'uint64': pa.array([1000, 2000, 3000], type=pa.uint64()),
    'bool': pa.array([True, False, True]),
    'time32_ms': pa.array([time(12, 34, 56, 123000), time(1, 23, 45), time(23, 59, 59)], type=pa.time32('ms')),
    'date32': pa.array([date(2025, 1, 1), date(2025, 6, 15), date(2025, 12, 31)]),
    'null_col': pa.array([None, None, None], type=pa.null()),
    'int64': pa.array([-1000000, 0, 1000000], type=pa.int64()),
    'time64_micro': pa.array([
        time(12, 34, 56, 123456),
        time(1, 23, 45, 654321),
        time(23, 59, 59, 999999)],
        type=pa.time64('us')),
    'time64_nano': pa.array([
        45296123456789,     # 12:34:56.123456789
        5025987654321,      # 01:23:45.987654321
        86399999999999],    # 23:59:59.999999999
        type=pa.time64('ns')),
    'timestamp_ms': pa.array([
        datetime(2025, 1, 1, 12, 0, 0, 123000),
        datetime(2025, 2, 15, 18, 30, 0),
        datetime(2025, 12, 31, 23, 59, 59, 999000)],
        type=pa.timestamp('ms')),
    'timestamp_ms_utc': pa.array([
        datetime(2025, 1, 1, 12, 0, 0, 123000, tzinfo=timezone.utc),
        datetime(2025, 2, 15, 18, 30, 0, tzinfo=timezone.utc),
        datetime(2025, 12, 31, 23, 59, 59, 999000, tzinfo=timezone.utc)],
        type=pa.timestamp('ms', tz='UTC')),
    'timestamp_us': pa.array([
        datetime(2025, 1, 1, 12, 0, 0, 123456),
        datetime(2025, 2, 15, 18, 30, 0, 654321),
        datetime(2025, 12, 31, 23, 59, 59, 999999)],
        type=pa.timestamp('us')),
    'timestamp_us_utc': pa.array([
        datetime(2025, 1, 1, 12, 0, 0, 123456, tzinfo=timezone.utc),
        datetime(2025, 2, 15, 18, 30, 0, 654321, tzinfo=timezone.utc),
        datetime(2025, 12, 31, 23, 59, 59, 999999, tzinfo=timezone.utc)],
        type=pa.timestamp('us', tz='UTC')),
    'timestamp_ns': pa.array([
        1735732800123456789,    # 2025.01.01D12:00:00.123456789
        1739644200987654321,    # 2025.02.15D18:30:00.987654321
        1767225599999999999],   # 2025.12.31D23:59:59.999999999
        type=pa.timestamp('ns')),
    'timestamp_ns_utc': pa.array([
        1735732800123456789,    # 2025.01.01D12:00:00.123456789
        1739644200987654321,    # 2025.02.15D18:30:00.987654321
        1767225599999999999],   # 2025.12.31D23:59:59.999999999
        type=pa.timestamp('ns', tz='UTC'))
}

# Create a table.
table = pa.table(data)

# Write to a Parquet file.
pq.write_table(table, '../tests/testdata/all_types.parquet')
