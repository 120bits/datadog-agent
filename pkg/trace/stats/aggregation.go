package stats

import (
	"strings"

	"github.com/DataDog/datadog-agent/pkg/trace/pb"
)

const (
	tagHostname   = "_dd.hostname"
	tagStatusCode = "http.status_code"
	tagVersion    = "version"
	tagOrigin     = "_dd.origin"
	tagSynthetic  = "synthetic"
)

// aggregation contains all the dimension on which we aggregate statistics
// when adding or removing fields to aggregation the methods toTagSet, keyLen and
// writeKey should always be updated accordingly
type aggregation struct {
	Env        string
	Resource   string
	Service    string
	Hostname   string
	StatusCode string
	Version    string
	Synthetic  bool
}

func newAggregationFromSpan(s *pb.Span, env string) aggregation {
	syntheticOrigin := isSynthetic(s.Meta[tagOrigin])

	return aggregation{
		Env:        env,
		Resource:   s.Resource,
		Service:    s.Service,
		Hostname:   s.Meta[tagHostname],
		StatusCode: s.Meta[tagStatusCode],
		Version:    s.Meta[tagVersion],
		Synthetic:  syntheticOrigin,
	}
}

func (aggr *aggregation) toTagSet() TagSet {
	tagSet := make(TagSet, 3, 7)
	tagSet[0] = Tag{"env", aggr.Env}
	tagSet[1] = Tag{"resource", aggr.Resource}
	tagSet[2] = Tag{"service", aggr.Service}
	if len(aggr.Hostname) > 0 {
		tagSet = append(tagSet, Tag{tagHostname, aggr.Hostname})
	}
	if len(aggr.StatusCode) > 0 {
		tagSet = append(tagSet, Tag{tagStatusCode, aggr.StatusCode})
	}
	if len(aggr.Version) > 0 {
		tagSet = append(tagSet, Tag{tagVersion, aggr.Version})
	}
	if aggr.Synthetic {
		tagSet = append(tagSet, Tag{tagSynthetic, "true"})
	}
	return tagSet
}

func (aggr *aggregation) keyLen() int {
	length := len("env:") + len(aggr.Env) + len(",resource:") + len(aggr.Resource) + len(",service:") + len(aggr.Service)
	if len(aggr.Hostname) > 0 {
		// +2 for "," and ":" separator
		length += 1 + len(tagHostname) + 1 + len(aggr.Hostname)
	}
	if len(aggr.StatusCode) > 0 {
		// +2 for "," and ":" separator
		length += 1 + len(tagStatusCode) + 1 + len(aggr.StatusCode)
	}
	if len(aggr.Version) > 0 {
		// +2 for "," and ":" separator
		length += 1 + len(tagVersion) + 1 + len(aggr.Version)
	}
	if aggr.Synthetic {
		// +2 for "," and ":" separator
		length += 1 + len(tagSynthetic) + 1 + len("true")
	}
	return length
}

func (aggr *aggregation) writeKey(b *strings.Builder) {
	b.WriteString("env:")
	b.WriteString(aggr.Env)
	b.WriteString(",resource:")
	b.WriteString(aggr.Resource)
	b.WriteString(",service:")
	b.WriteString(aggr.Service)

	// Keys should be written in lexicographical order of the tag name
	if len(aggr.Hostname) > 0 {
		b.WriteString("," + tagHostname + ":")
		b.WriteString(aggr.Hostname)
	}
	if len(aggr.StatusCode) > 0 {
		b.WriteString("," + tagStatusCode + ":")
		b.WriteString(aggr.StatusCode)
	}
	if len(aggr.Version) > 0 {
		b.WriteString("," + tagVersion + ":")
		b.WriteString(aggr.Version)
	}
	if aggr.Synthetic {
		b.WriteString("," + tagSynthetic + ":")
		b.WriteString("true")
	}
}

// isSynthetic determines if the origin indicates synthetic data
// for now, we assume that synthetic data origins will begin with "synthetics"
func isSynthetic(origin string) bool {
	return strings.HasPrefix(origin, "synthetics")
}
